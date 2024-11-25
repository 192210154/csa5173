#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 16 

void print_block(const char *label, uint8_t *block, int size) {
    printf("%s: ", label);
    for (int i = 0; i < size; i++) {
        printf("%02X", block[i]);
    }
    printf("\n");
}

void left_shift(uint8_t *input, uint8_t *output, int size) {
    uint8_t carry = 0;
    for (int i = size - 1; i >= 0; i--) {
        uint8_t next_carry = input[i] >> 7;
        output[i] = (input[i] << 1) | carry;
        carry = next_carry;
    }
}

void generate_subkeys(uint8_t *key, uint8_t *K1, uint8_t *K2, int block_size, uint8_t Rb) {
    uint8_t L[BLOCK_SIZE] = {0};
    uint8_t zero_block[BLOCK_SIZE] = {0};
    memcpy(L, key, block_size); 

    print_block("L (after block cipher encryption)", L, block_size);

    left_shift(L, K1, block_size);
    if (L[0] & 0x80) { 
        K1[block_size - 1] ^= Rb;
    }
    print_block("K1", K1, block_size);

    left_shift(K1, K2, block_size);
    if (K1[0] & 0x80) { 
        K2[block_size - 1] ^= Rb;
    }
    print_block("K2", K2, block_size);
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 
                               0xab, 0xf7, 0xcf, 0x9f, 0x83, 0x20, 0x1c, 0x4b}; 
    uint8_t K1[BLOCK_SIZE] = {0};
    uint8_t K2[BLOCK_SIZE] = {0};

    uint8_t Rb = 0x87; 
    printf("Block size: %d bits\n", BLOCK_SIZE * 8);

    generate_subkeys(key, K1, K2, BLOCK_SIZE, Rb);

    return 0;
}

