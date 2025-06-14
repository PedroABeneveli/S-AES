#ifndef UTILS
#define UTILS

#include "globals.h"

// 3 funcoes de conversao pra base 64, pra lidar com cada caso de padding

// base64 com 3 bytes
string to_base64(int8_t c1, int8_t c2, int8_t c3);

// base64 com 2 bytes
string to_base64(int8_t c1, int8_t c2);

// base 64 com 1 byte
string to_base64(int8_t c1);

#endif