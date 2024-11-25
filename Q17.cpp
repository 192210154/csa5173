#include <stdio.h>
#include <stdint.h>

static const int PC1[] = {
    57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15, 7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4
};

static const int PC2[] = {
    14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21, 10, 23, 19, 12, 4,
    26, 8, 16, 7, 27, 20, 13, 2, 41, 52, 31, 37, 47, 55, 30, 40,
    51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32
};

static const int SHIFT_SCHEDULE[] = {
    1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1
};

void permute(uint8_t *input, uint8_t *output, const int *table, int n) {
    for (int i = 0; i < n; i++) {
        output[i] = input[table[i] - 1];
    }
}

void leftShift(uint8_t *key, int n) {
    uint8_t temp[28];
    for (int i = 0; i < 28; i++) {
        temp[i] = key[(i + n) % 28];
    }
    for (int i = 0; i < 28; i++) {
        key[i] = temp[i];
    }
}

void generateSubkeys(uint8_t *mainKey, uint8_t subkeys[16][48]) {
    uint8_t permutedKey[56];
    uint8_t C[28], D[28];
    uint8_t CD[56];

    permute(mainKey, permutedKey, PC1, 56);

    for (int i = 0; i < 28; i++) {
        C[i] = permutedKey[i];
        D[i] = permutedKey[i + 28];
    }

    for (int i = 0; i < 16; i++) {
        leftShift(C, SHIFT_SCHEDULE[i]);
        leftShift(D, SHIFT_SCHEDULE[i]);

        for (int j = 0; j < 28; j++) {
            CD[j] = C[j];
            CD[j + 28] = D[j];
        }

        permute(CD, subkeys[i], PC2, 48);
    }
}

void printKey(uint8_t *key, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", key[i]);
    }
    printf("\n");
}

int main() {
    uint8_t mainKey[36] = {
        0, 0, 1, 0, 0, 0,   
        0, 1, 1, 0, 0, 0, 
        1, 0, 0, 1, 0, 1, 
        1, 1, 0, 1, 1, 1, 
        0, 1, 1, 1, 0, 1, 
        1, 1, 1, 0, 0, 0, 
        
    };

    uint8_t subkeys[16][48];

    generateSubkeys(mainKey, subkeys);

    for (int i = 0; i < 16; i++) {
        printf("Subkey %d: ", i + 1);
        printKey(subkeys[i], 48);
    }

    printf("\nSubkeys for decryption (reversed order):\n");
    for (int i = 15; i >= 0; i--) {
        printf("Subkey %d: ", 16 - i);
        printKey(subkeys[i], 48);
    }

    return 0;
}

