#include "operations.h"
#include "GaloisField.h"

NibbleMatrix addRoundKey(NibbleMatrix data, NibbleMatrix key, bool print) {
    NibbleMatrix result = data ^ key;

    if (print) {
        cout << "addRoundKey:\n";
        cout << "    |   Data    |    Key    |    XOR    |\n";
        cout << "    | " << data.nibbles[0][0] << " " << data.nibbles[0][1] << " | " << key.nibbles[0][0] << " " << key.nibbles[0][1] << " | " << result.nibbles[0][0] << " " << result.nibbles[0][1] << " |\n";
        cout << "    | " << data.nibbles[1][0] << " " << data.nibbles[1][1] << " | " << key.nibbles[1][0] << " " << key.nibbles[1][1] << " | " << result.nibbles[1][0] << " " << result.nibbles[1][1] << " |\n";
        cout << "\n";
    } 

    return result;
}

// S-Box fixa utilizada na funcao subNibbles
bitset<4> sbox[4][4] = {
    {bitset<4>(9), bitset<4>(4), bitset<4>(10), bitset<4>(11)},
    {bitset<4>(13), bitset<4>(1), bitset<4>(8), bitset<4>(5)},
    {bitset<4>(6), bitset<4>(2), bitset<4>(0), bitset<4>(3)},
    {bitset<4>(12), bitset<4>(14), bitset<4>(15), bitset<4>(7)}
};

NibbleMatrix subNibbles(NibbleMatrix data, bool print) {
    NibbleMatrix result;
    int num;

    for (int i = 0 ; i < 2 ; i++) {
        for (int j = 0 ; j < 2 ; j++) {
            num = (int)(data.nibbles[i][j].to_ulong());

            // uso os 2 bits mais significativos para o indice da linha, e isolo os 2 menos para o indice da coluna
            result.nibbles[i][j] = sbox[num>>2][num&3];
        }
    }

    if (print) {
        cout << "subNibbles:\n";
        cout << "    |   Data    |  Subbed   |\n";
        cout << "    | " << data.nibbles[0][0] << " " << data.nibbles[0][1] << " | " << result.nibbles[0][0] << " " << result.nibbles[0][1] << " |\n";
        cout << "    | " << data.nibbles[1][0] << " " << data.nibbles[1][1] << " | " << result.nibbles[1][0] << " " << result.nibbles[1][1] << " |\n";
        cout << "\n";
    }

    return result;
}

NibbleMatrix shiftRows(NibbleMatrix data, bool print) {
    NibbleMatrix result = data;

    swap(result.nibbles[1][0], result.nibbles[1][1]);

    if (print) {
        cout << "shiftRows:\n";
        cout << "    |   Data    |  Shifted  |\n";
        cout << "    | " << data.nibbles[0][0] << " " << data.nibbles[0][1] << " | " << result.nibbles[0][0] << " " << result.nibbles[0][1] << " |\n";
        cout << "    | " << data.nibbles[1][0] << " " << data.nibbles[1][1] << " | " << result.nibbles[1][0] << " " << result.nibbles[1][1] << " |\n";
        cout << "\n";
    }

    return result;
}

NibbleMatrix mixColumns(NibbleMatrix data, bool print) {
    NibbleMatrix mixer, result;;

    // matriz escolhida pelo algoritmo para realizar esse mix
    mixer.nibbles[0][0] = 1; mixer.nibbles[0][1] = 4;
    mixer.nibbles[1][0] = 4; mixer.nibbles[1][1] = 1;

    // Na especificacao, a multiplicacao eh feita uma coluna por vez, mas pela propria propriedade de multiplicacoes de matrizes, se multiplicarmos o mixer pela matrix da mensagem inteira, teremos o mesmo resultado
    result = mixer * data;

    if (print) {
        cout << "mixColumns:\n";
        cout << "    |   Data    |   Mixed   |\n";
        cout << "    | " << data.nibbles[0][0] << " " << data.nibbles[0][1] << " | " << result.nibbles[0][0] << " " << result.nibbles[0][1] << " |\n";
        cout << "    | " << data.nibbles[1][0] << " " << data.nibbles[1][1] << " | " << result.nibbles[1][0] << " " << result.nibbles[1][1] << " |\n";
        cout << "\n";
    }

    return result;
}

bitset<8> g_function(bitset<8> half, int index, bool print) {
    bitset<4> L, R;
    int num;

    L = (int) (half >> 4).to_ulong();
    R = (int) (half & bitset<8>(15)).to_ulong();

    // RotWord
    swap(L, R);

    // SubWord, aplicacao da sbox
    num = (int) L.to_ulong();
    L = sbox[num>>2][num&3];

    num = (int) R.to_ulong();
    R = sbox[num>>2][num&3];

    // XOR com Rcon

    // Rcon = x**2 * x**(index)
    // pra calcular o Rcon, vou fazer a exponenciacao fazendo uma sequencia de multiplicacoes
    GaloisField16 rcon(4);
    for (int i = 0 ; i < index ; i++)
        rcon = rcon * GaloisField16(2);

    L = L ^ rcon.polinomial;
    R = R ^ bitset<4>(0);

    bitset<8> result;
    int num_L, num_R;

    num_L = (int) L.to_ulong();
    num_R = (int) R.to_ulong();

    result = (num_L << 4) + num_R;

    if (print) {
        cout << "g_function com index " << index << ":\n";
        cout << "    " << half << " -> " << result << "\n\n";
    }

    return result;
}

array<NibbleMatrix, 3> keyExpansion(int16_t key, bool print) {
    // Ja retorno NibbleMatrix para facilitar na hora de realizar a criptografia
    array<NibbleMatrix, 3> keys;
    bitset<8> L, R, g_return;
    int num_L, num_R;
    int16_t roundKey;

    if (print) {
        cout << "keyExpansion com a chave " << bitset<16>(key) << ":\n\n";
    }

    roundKey = key;
    for (int i = 0 ; i < 2 ; i++) {
        keys[i] = NibbleMatrix(roundKey);

        L = roundKey >> 8;
        R = roundKey & 0xffff;
        g_return = g_function(R, i+1, print);   // o index da g_function eh indexado em 1

        L = L ^ g_return;
        R = R ^ L;

        num_L = (int) L.to_ulong();
        num_R = (int) R.to_ulong();
        roundKey = (num_L << 8) + num_R;
    }
    keys[2] = NibbleMatrix(roundKey);

    if (print) {
        cout << "Chaves geradas:\n";
        cout << "    Key0 = " << keys[0].nibbles[0][0] << " " << keys[0].nibbles[1][0] << " " << keys[0].nibbles[0][1] << " " << keys[0].nibbles[1][1] << "\n";
        cout << "    Key1 = " << keys[1].nibbles[0][0] << " " << keys[1].nibbles[1][0] << " " << keys[1].nibbles[0][1] << " " << keys[1].nibbles[1][1] << "\n";
        cout << "    Key2 = " << keys[2].nibbles[0][0] << " " << keys[2].nibbles[1][0] << " " << keys[2].nibbles[0][1] << " " << keys[2].nibbles[1][1] << "\n";
        cout << "\n";
    }

    return keys;
}