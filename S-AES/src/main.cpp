#include "globals.h"
#include "utils.h"
#include "encrypt.h"

int main() {
    int op;
    string temp;
    int16_t key, plain_text, cipher_text;
    int8_t byte1, byte2;

    do {
        cout << "\n------------------------------------------------------------------------------------------------\n";
        cout << "\nDigite:\n";
        cout << "1 para realizar uma encriptacao com o S-AES;\n";
        cout << "0 para terminar a execucao do programa.\n";

        cin >> op;
        getchar();

        if (op == 1) {
            cout << "\nDigite a chave em binario (16 bits):\n";
            cin >> temp;
            getchar();

            if ((int) temp.size() != 16) {
                cout << "\nChave com tamanho diferente de 16. Coloque todos os bits da chave juntos para que o programa leia a chave corretamente.\n";
                continue;
            }

            bool is_bin = true;
            for (int i = 0 ; i < 16 ; i++) {
                if (temp[i] != '0' && temp[i] != '1') {
                    is_bin = false;
                    break;
                }
            }

            if (!is_bin) {
                cout << "\nChave nao binaria. Por favor coloque a chave em binario para o correto funcionamento do programa.\n";
                continue;
            }

            key = (int16_t) bitset<16>(temp).to_ulong();

            cout << "\nDigite o texto em claro (2 caracteres):\n";
            cin >> temp;
            getchar();

            if ((int) temp.size() != 2) {
                cout << "\nTexto com tamanho diferente de 2. Lembrando que sinais de pontuacao tambem sao considerados caracteres.\n";
                continue;
            }

            plain_text = (((int16_t) temp[0]) << 8) + ((int16_t) temp[1]);

            cipher_text = saes_encrypt(plain_text, key, true);
            byte1 = cipher_text >> 8;
            byte2 = cipher_text & 0xff;

            cout << "Texto cifrado em hexadecimal: 0x" << setfill('0') << setw(4) << right << hex << cipher_text << "\n";
            cout << "Texto cifrado em base64: " << to_base64(byte1, byte2) << "\n";
        } else if (op != 0)
            cout << "\nOperacao invalida\n";

        if (op) {
            cout << "\nAperte Enter para continuar.";
            getline(cin, temp); 
        }
    } while (op != 0);

    return 0;
}