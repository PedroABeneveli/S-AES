#include "NibbleMatrix.h"

NibbleMatrix::NibbleMatrix() {}
NibbleMatrix::NibbleMatrix(int16_t val) {
    nibbles[0][0] = val >> 12;
    nibbles[1][0] = (val >> 8) & 0xF;
    nibbles[0][1] = (val >> 4) & 0xF;
    nibbles[1][1] = val & 0xF;
}

NibbleMatrix NibbleMatrix::operator^(const NibbleMatrix &o) {
    NibbleMatrix result;

    result.nibbles[0][0] = nibbles[0][0] ^ o.nibbles[0][0];
    result.nibbles[0][1] = nibbles[0][1] ^ o.nibbles[0][1];
    result.nibbles[1][0] = nibbles[1][0] ^ o.nibbles[1][0];
    result.nibbles[1][1] = nibbles[1][1] ^ o.nibbles[1][1];

    return result;
}