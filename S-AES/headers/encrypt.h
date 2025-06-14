#ifndef ENCRYPT
#define ENCRYPT

#include "globals.h"

int16_t saes_encrypt(int16_t plain_text, int16_t key, bool print=false);

string encrypt_saes_ecb(string plain_text, int16_t key, bool print=false);

#endif