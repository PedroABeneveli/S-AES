#ifndef ENCRYPT
#define ENCRYPT

#include "globals.h"

uint16_t saes_encrypt(uint16_t plain_text, uint16_t key, bool print=false);

string encrypt_saes_ecb(string plain_text, uint16_t key, bool print=false);

#endif