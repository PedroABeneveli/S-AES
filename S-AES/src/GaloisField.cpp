#include "GaloisField.h"

// Construtores
GaloisField16::GaloisField16() {}
GaloisField16::GaloisField16(bitset<4> x) {
    polinomial = x;
}

void GaloisField16::operator=(const bitset<4> &o) {
    polinomial = o;
}

// Soma dos coeficientes do polinomio mod 2, ou seja, XOR entre os coeficientes
GaloisField16 GaloisField16::operator+(const GaloisField16 &o) {
    return GaloisField16(polinomial ^ o.polinomial);
}

// Produto de dois polinomios em GF(16)
GaloisField16 GaloisField16::operator*(const GaloisField16 &o) {
    // aqui, utilizamos o fato que x**4 eh congruente a x + 1
    // entao, ao realizarmos os shifts necessarios para a multiplicacao binaria, sempre que um termo x**4 sera criado, o substituimos por x + 1
    // portanto, por isso foi implementado o algoritmo classico da multiplicacao, para facilitar a observacao desse fenomeno e a codificacao do algoritmo

    bitset<4> result(0), mul1, mul2;
    bool add_3;

    mul1 = polinomial;
    mul2 = o.polinomial;
    while (mul2 != 0) {

        // se o digito do numero de "baixo" for 1, somamos a resposta da multiplicacao
        if (mul2[0])
            result ^= mul1;
        
        // verificamos se um termo x**4 sera criado, para troca-lo por x+1 depois de deslizar o numero de "cima"
        add_3 = false;
        if (mul1[3])
            add_3 = true;

        // deslizamos o numero de "cima" para a esquerda, como no algoritmo classico da multiplicacao, e o de "baixo" para direita para descartar os bits ja analisados
        mul1 <<= 1;
        mul2 >>= 1;
        if (add_3)
            mul1 ^= bitset<4>(3);
    }

    return GaloisField16(result);
}