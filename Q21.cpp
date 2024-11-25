#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BLOCK_SIZE 8
#define MAX_BLOCKS 10

void xor_blocks(uint8_t *a, uint8_t *b, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}
int pad_message(uint8_t *plaintext, int plaintext_len, uint8_t *padded_plaintext) {
    memcpy(padded_plaintext, plaintext, plaintext_len);
    int padding_len = BLOCK_SIZE - (plaintext_len % BLOCK_SIZE);
    padded_plaintext[plaintext_len] = 0x80;
    for (int i = plaintext_len + 1; i < plaintext_len + padding_len; i++) {
        padded_plaintext[i] = 0x00; 
    }
    return plaintext_len + padding_len;
}
void ecb_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, int blocks) {
    for (int i = 0; i < blocks; i++) {
        xor_blocks(plaintext + i * BLOCK_SIZE, &key, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}
void cbc_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t *iv, int blocks) {
    uint8_t temp_block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < blocks; i++) {
        xor_blocks(plaintext + i * BLOCK_SIZE, prev_block, temp_block, BLOCK_SIZE);
        xor_blocks(temp_block, &key, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}
void cfb_mode(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t *iv, int blocks) {
    uint8_t temp_block[BLOCK_SIZE];
    uint8_t prev_block[BLOCK_SIZE];
    memcpy(prev_block, iv, BLOCK_SIZE);

    for (int i = 0; i < blocks; i++) {
        xor_blocks(prev_block, &key, temp_block, BLOCK_SIZE);
        xor_blocks(temp_block, plaintext + i * BLOCK_SIZE, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
        memcpy(prev_block, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
    }
}

int main() {
 
    uint8_t plaintext[] = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66}; 
    uint8_t iv[BLOCK_SIZE] = {0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF, 0x00, 0x11}; 
    uint8_t key = 0x5A; 
    uint8_t padded_plaintext[MAX_BLOCKS * BLOCK_SIZE];
    uint8_t ciphertext[MAX_BLOCKS * BLOCK_SIZE];
    uint8_t decrypted[MAX_BLOCKS * BLOCK_SIZE];

    int plaintext_len = sizeof(plaintext);
    int padded_len = pad_message(plaintext, plaintext_len, padded_plaintext);
    int blocks = padded_len / BLOCK_SIZE;
    printf("ECB Mode:\n");
    ecb_mode(padded_plaintext, ciphertext, key, blocks);
    printf("Ciphertext: ");
    for (int i = 0; i < blocks * BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    printf("\nCBC Mode:\n");
    cbc_mode(padded_plaintext, ciphertext, key, iv, blocks);
    printf("Ciphertext: ");
    for (int i = 0; i < blocks * BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");
    printf("\nCFB Mode:\n");
    cfb_mode(padded_plaintext, ciphertext, key, iv, blocks);
    printf("Ciphertext: ");
    for (int i = 0; i < blocks * BLOCK_SIZE; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}

