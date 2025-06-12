#ifndef GALOISF
#define GALOISF

#include "globals.h"

// implementacao das operacoes em GF(16)
struct GaloisField16 {
    bitset<4> polinomial;

    GaloisField16();
    GaloisField16(bitset<4> x);

    // o produto eh reduzido mod x**4 + x + 1

    GaloisField16 operator*(const GaloisField16 &o);
    GaloisField16 operator+(const GaloisField16 &o);

    // Atribuicao para deixar outros codigos menos verbosos
    void operator=(const bitset<4> &o);
};

#endif