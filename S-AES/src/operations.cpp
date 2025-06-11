#include "operations.h"

NibbleMatrix addRoundKey(NibbleMatrix data, NibbleMatrix key, bool print) {
    NibbleMatrix result = data ^ key;

    if (print) {
        cout << "addRoundKey:\n";
        cout << "    |   Data    |    Key    |    XOR    |\n";
        cout << "    | " << data.nibbles[0][0] << " " << data.nibbles[0][1] << " | " << key.nibbles[0][0] << " " << key.nibbles[0][1] << " | " << result.nibbles[0][0] << " " << result.nibbles[0][1] << " |\n";
        cout << "    | " << data.nibbles[1][0] << " " << data.nibbles[1][1] << " | " << key.nibbles[1][0] << " " << key.nibbles[1][1] << " | " << result.nibbles[1][0] << " " << result.nibbles[1][1] << " |\n";
        cout << "\n";
    } 

    return result;
}