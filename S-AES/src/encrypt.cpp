#include "encrypt.h"
#include "NibbleMatrix.h"
#include "operations.h"

int16_t saes_encrypt(int16_t plain_text, int16_t key, bool print) {
    NibbleMatrix message(plain_text);
    array<NibbleMatrix, 3> keys = keyExpansion(key, print);

    if (print) {
        cout << "Mensagem em claro:\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    message = addRoundKey(message, keys[0], print);

    // 1a Rodada
    message = subNibbles(message, print);
    message = shiftRows(message, print);
    message = mixColumns(message, print);
    message = addRoundKey(message, keys[1]);

    if (print) {
        cout << "Mensagem apos a 1a rodada:\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    // 2a Rodada
    message = subNibbles(message, print);
    message = shiftRows(message, print);
    message = addRoundKey(message, keys[2]);

    if (print) {
        cout << "Texto cifrado:\n";
        cout << "    " << message.nibbles[0][0] << " " << message.nibbles[0][1] << "\n";
        cout << "    " << message.nibbles[1][0] << " " << message.nibbles[1][1] << "\n";
        cout << "\n";
    }

    int16_t cipher_text = message.to_int16();

    return cipher_text;
}