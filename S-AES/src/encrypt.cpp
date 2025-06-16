#include "encrypt.h"
#include "NibbleMatrix.h"
#include "operations.h"
#include "utils.h"

uint16_t saes_encrypt(uint16_t plain_text, uint16_t key, bool print) {
    NibbleMatrix message(plain_text);
    array<NibbleMatrix, 3> keys = keyExpansion(key, print);

    if (print) {
        cout << "Mensagem em claro:\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    message = addRoundKey(message, keys[0], print);

    if (print) {
        cout << "------------------------------------------\n";
        cout << "Primeira Rodada:\n\n";
    }

    // 1a Rodada
    message = subNibbles(message, print);
    message = shiftRows(message, print);
    message = mixColumns(message, print);
    message = addRoundKey(message, keys[1], print);

    if (print) {
        cout << "------------------------------------------\n\n";
        cout << "Mensagem apos a 1a rodada:\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    if (print) {
        cout << "------------------------------------------\n";
        cout << "Segunda Rodada:\n\n";
    }

    // 2a Rodada
    message = subNibbles(message, print);
    message = shiftRows(message, print);
    message = addRoundKey(message, keys[2], print);

    if (print) {
        cout << "------------------------------------------\n\n";
        cout << "Texto cifrado (apos a 2a Rodada):\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    uint16_t cipher_text = message.to_int16();

    return cipher_text;
}

string encrypt_saes_ecb(string plain_text, uint16_t key, bool print) {
    queue<uint8_t> to_process;   // bytes a serem convertidos em base64
    string cipher_text = "";
    uint16_t plain_block, cipher_block;
    uint8_t half1, half2, half3;

    // assumindo que o texto tem quantidade par de caracteres
    for (int i = 0 ; i < (int) plain_text.size() ; i += 2) {
        plain_block = (((uint16_t) plain_text[i]) << 8) + ((uint16_t) plain_text[i+1]);

        cipher_block = saes_encrypt(plain_block, key);

        if (print) {
            cout << "Bloco " << dec << i/2 << " em hexadecimal: 0x" << setfill('0') << setw(4) << right << hex << cipher_block << "\n";
        }

        half1 = (cipher_block >> 8) & 0xff;
        half2 = cipher_block & 0xff;
        to_process.push(half1);
        to_process.push(half2);

        while ((int) to_process.size() >= 3) {
            half1 = to_process.front(); to_process.pop();
            half2 = to_process.front(); to_process.pop();
            half3 = to_process.front(); to_process.pop();

            cipher_text += to_base64(half1, half2, half3);
        }
    }

    if ((int) to_process.size() == 2) {
        half1 = to_process.front(); to_process.pop();
        half2 = to_process.front(); to_process.pop();

        cipher_text += to_base64(half1, half2);
    }

    if ((int) to_process.size() == 1) {
        half1 = to_process.front(); to_process.pop();

        cipher_text += to_base64(half1);
    }

    return cipher_text;
}