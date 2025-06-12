#include "operations.h"

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