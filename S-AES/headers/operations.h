#ifndef OPERATIONS
#define OPERATIONS

#include "globals.h"
#include "NibbleMatrix.h"

// Funcao addRoundKey, que realiza adicao do dado com a chave modulo 2, ou seja, realiza um XOR entre a entrada e a chave dada
NibbleMatrix addRoundKey(NibbleMatrix data, NibbleMatrix key, bool print=false);

// Uso de S-Box pra cada Nibble da Matriz
NibbleMatrix subNibbles(NibbleMatrix data, bool print=false);

// Faz um swap dos nibbles nas posicoes [1][0] e [1][1]
NibbleMatrix shiftRows(NibbleMatrix data, bool print=false);

#endif