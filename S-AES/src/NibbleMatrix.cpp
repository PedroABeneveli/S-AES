#include "NibbleMatrix.h"
#include "GaloisField.h"

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

NibbleMatrix NibbleMatrix::operator*(const NibbleMatrix &o) {
    GaloisField16 op1, op2, acc;
    NibbleMatrix result;

    for (int i = 0 ; i < 2 ; i++) {
        for (int j = 0 ; j < 2 ; j++) {
            acc = GaloisField16(0);

            for (int k = 0 ; k < 2 ; k++) {
                op1 = nibbles[i][k];
                op2 = o.nibbles[k][j];

                acc = acc + (op1 * op2);
            }

            result.nibbles[i][j] = acc.polinomial;
        }
    }

    return result;
}

int16_t NibbleMatrix::to_int16() {
    int16_t result = 0;

    result += ((int) nibbles[0][0].to_ulong()) << 12;
    result += ((int) nibbles[1][0].to_ulong()) << 8;
    result += ((int) nibbles[0][1].to_ulong()) << 4;
    result += ((int) nibbles[1][1].to_ulong());

    return result;
}