#include <stdio.h>
#include <stdint.h>

static const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

static const int PC2[] = {
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

static const int SHIFTS[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void permute(uint8_t *input, uint8_t *output, const int *table, int size) {
    for (int i = 0; i < size; i++) {
        int bit = (input[(table[i] - 1) / 8] >> (7 - ((table[i] - 1) % 8))) & 1;
        output[i / 8] |= bit << (7 - (i % 8));
    }
}

void leftShift(uint8_t *key, int shift, int size) {
    uint8_t temp[28];
    for (int i = 0; i < size; i++) {
        temp[i] = key[(i + shift) % size];
    }
    for (int i = 0; i < size; i++) {
        key[i] = temp[i];
    }
}

void generateSubkeys(uint8_t *mainKey, uint8_t subkeys[16][6]) {
    uint8_t permutedKey[7] = {0};
    uint8_t C[4] = {0};
    uint8_t D[4] = {0};

    permute(mainKey, permutedKey, PC1, 56);

    for (int i = 0; i < 3; i++) {
        C[i] = permutedKey[i];
        D[i] = permutedKey[i + 3];
    }
    C[3] = permutedKey[3] & 0xF0;
    D[3] = (permutedKey[3] & 0x0F) << 4;

    for (int round = 0; round < 16; round++) {
        leftShift(C, SHIFTS[round], 28);
        leftShift(D, SHIFTS[round], 28);

        uint8_t combinedKey[7] = {0};
        for (int i = 0; i < 3; i++) {
            combinedKey[i] = C[i];
            combinedKey[i + 3] = D[i];
        }
        combinedKey[3] = (C[3] & 0xF0) | ((D[3] & 0xF0) >> 4);
        combinedKey[4] = ((D[3] & 0x0F) << 4);

      
        permute(combinedKey, subkeys[round], PC2, 48);
    }
}

void printKey(uint8_t *key, int length) {
    for (int i = 0; i < length; i++) {
        printf("%02X", key[i]);
    }
    printf("\n");
}

int main() {
   
    uint8_t mainKey[8] = {
        0x13, 0x34, 0x57, 0x79, 0x9B, 0xBC, 0xDF, 0xF1
    };

    uint8_t subkeys[16][6];

    generateSubkeys(mainKey, subkeys);

    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: ", i + 1);
        printKey(subkeys[i], 6);
    }

    return 0;
}

