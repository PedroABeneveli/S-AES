#include "utils.h"

// essa string eh equivalente a tabela de conversao, pois cada indice da string corresponde ao caracter equivalente em base64
string table = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

string to_base64(int8_t c1, int8_t c2, int8_t c3) {
    int idx; 
    string text = "";

    // primeiro caracter
    // pega os 6 bits mais significativos do primeiro byte
    idx = c1 >> 2; 
    text.push_back(table[idx]);

    // segundo caracter
    // junta os 2 menos significativos do segundo byte com os 4 mais significativos do segundo
    idx = ((c1 & 3) << 4) + (c2 >> 4);
    text.push_back(table[idx]);

    // terceiro caracter
    // junta os 4 menos sig do segundo byte com os 2 mais sig do terceiro byte
    idx = ((c2 & 0xf) << 2) + (c3 >> 6);
    text.push_back(table[idx]);

    // quarto caracter
    // pega os 6 bits menos significativos do terceiro bit
    idx = c3 & 0x3f;
    text.push_back(table[idx]);

    return text;
}

string to_base64(int8_t c1, int8_t c2) {
    int idx;
    string text = "";

    // primeiro caracter
    idx = c1 >> 2; 
    text.push_back(table[idx]);

    // segundo caracter
    idx = ((c1 & 3) << 4) + (c2 >> 4);
    text.push_back(table[idx]);

    // terceiro caracter
    // o que seria os bits do terceiro byte, substituimos por 0
    idx = ((c2 & 0xf) << 2);
    text.push_back(table[idx]);

    // padding
    text.push_back('=');

    return text;
}

string to_base64(int8_t c1) {
    int idx;
    string text = "";

    // primeiro caracter
    idx = c1 >> 2; 
    text.push_back(table[idx]);

    // segundo caracter, preenchendo que seria do segundo byte com 0s
    idx = ((c1 & 3) << 4);
    text.push_back(table[idx]);

    // padding
    text += "==";

    return text;
}