#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8 

void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}
void sdes_encrypt(uint8_t *block, uint8_t key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ (key & 1); 
    }
}
void sdes_decrypt(uint8_t *block, uint8_t key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = block[i] ^ (key & 1); 
    }
}
void cbc_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t *iv, int blocks) {
    uint8_t temp_block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];

    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < blocks; i++) {
        xor_blocks(plaintext + i * BLOCK_SIZE, prev_block, temp_block, BLOCK_SIZE);
        sdes_encrypt(temp_block, key, ciphertext + i * BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

void cbc_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t key, uint8_t *iv, int blocks) {
    uint8_t temp_block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];

    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < blocks; i++) {
        sdes_decrypt(ciphertext + i * BLOCK_SIZE, key, temp_block);
        xor_blocks(temp_block, prev_block, plaintext + i * BLOCK_SIZE, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

int main() {
 
    uint8_t plaintext[] = {0, 0, 0, 1, 0, 1, 0, 0}; 
    uint8_t iv[BLOCK_SIZE] = {1, 0, 1, 0, 1, 0, 1, 0}; 
    uint8_t key = 0x7D; 

    int blocks = 1;
    uint8_t ciphertext[BLOCK_SIZE * blocks];
    uint8_t decryptedtext[BLOCK_SIZE * blocks];

    printf("Original Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", plaintext[i]);
    }
    printf("\n");

    cbc_encrypt(plaintext, ciphertext, key, iv, blocks);

    printf("Ciphertext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", ciphertext[i]);
    }
    printf("\n");

    cbc_decrypt(ciphertext, decryptedtext, key, iv, blocks);

    printf("Decrypted Plaintext: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%d", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

