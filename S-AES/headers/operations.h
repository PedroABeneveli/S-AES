#ifndef OPERATIONS
#define OPERATIONS

#include "globals.h"
#include "NibbleMatrix.h"

// Funcao addRoundKey, que realiza adicao do dado com a chave modulo 2, ou seja, realiza um XOR entre a entrada e a chave dada
NibbleMatrix addRoundKey(NibbleMatrix data, NibbleMatrix key, bool print=false);

#endif