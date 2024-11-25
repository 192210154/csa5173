#include <stdio.h>
#include <stdint.h>
#include <string.h>

uint8_t S_BOX[4][16] = {
    {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
    {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
    {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
    {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
};

int INITIAL_PERMUTATION[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17,  9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

int FINAL_PERMUTATION[64] = {
    40,  8, 48, 16, 56, 24, 64, 32,
    39,  7, 47, 15, 55, 23, 63, 31,
    38,  6, 46, 14, 54, 22, 62, 30,
    37,  5, 45, 13, 53, 21, 61, 29,
    36,  4, 44, 12, 52, 20, 60, 28,
    35,  3, 43, 11, 51, 19, 59, 27,
    34,  2, 42, 10, 50, 18, 58, 26,
    33,  1, 41,  9, 49, 17, 57, 25
};
uint64_t permute(uint64_t input, const int *table, int n) {
    uint64_t output = 0;
    for (int i = 0; i < n; i++) {
        output |= ((input >> (64 - table[i])) & 1) << (n - 1 - i);
    }
    return output;
}
uint32_t feistel_function(uint32_t half_block, uint64_t subkey) {
    uint32_t expanded = (half_block << 4) | (half_block >> 28); // Simplified expansion
    uint32_t xored = expanded ^ (uint32_t)(subkey & 0xFFFFFFFF); // XOR with subkey

    uint32_t substituted = 0;
    for (int i = 0; i < 8; i++) {
        int row = ((xored >> (4 * i)) & 0x8) | ((xored >> (4 * i)) & 0x1);
        int col = (xored >> (4 * i)) & 0xE;
        substituted |= S_BOX[row][col] << (4 * i);
    }

    return substituted;
}
uint64_t des(uint64_t plaintext, uint64_t key, int mode) {
    uint64_t permuted_block = permute(plaintext, INITIAL_PERMUTATION, 64);

    uint32_t left = (uint32_t)(permuted_block >> 32);
    uint32_t right = (uint32_t)(permuted_block & 0xFFFFFFFF);

    uint64_t subkeys[16];
    for (int i = 0; i < 16; i++) {
        subkeys[i] = key; 
    }
    for (int round = 0; round < 16; round++) {
        uint64_t subkey = (mode == 0) ? subkeys[round] : subkeys[15 - round];
        uint32_t new_right = left ^ feistel_function(right, subkey);
        left = right;
        right = new_right;
    }

    uint64_t pre_output = ((uint64_t)right << 32) | left;
    uint64_t ciphertext = permute(pre_output, FINAL_PERMUTATION, 64);

    return ciphertext;
}

int main() {
    uint64_t plaintext = 0x123456789ABCDEF0;
    uint64_t key = 0x133457799BBCDFF1;

    printf("Plaintext: %016lX\n", plaintext);

    uint64_t ciphertext = des(plaintext, key, 0);
    printf("Ciphertext: %016lX\n", ciphertext);

    uint64_t decrypted = des(ciphertext, key, 1);
    printf("Decrypted: %016lX\n", decrypted);

    return 0;
}

