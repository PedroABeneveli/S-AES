#ifndef NIB_MATRIX
#define NIB_MATRIX

#include "globals.h"

// struct criada para permitir a facil passagem e retorno de matrizes de nibbles pelas funcoes
struct NibbleMatrix {
    bitset<4> nibbles[2][2];

    // Construtores
    NibbleMatrix();
    NibbleMatrix(uint16_t val);

    // XOR
    NibbleMatrix operator^(const NibbleMatrix &o);

    // Multiplicacao de Matrixes em GF(16)
    NibbleMatrix operator*(const NibbleMatrix &o);

    uint16_t to_int16();
};

#endif