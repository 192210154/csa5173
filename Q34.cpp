#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>

#define BLOCK_SIZE 8

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}
void dummy_block_cipher(uint8_t *input, uint8_t *key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ key[i]; 
    }
}
void pad_message(uint8_t *message, int msg_len, uint8_t *padded_msg, int padded_len) {
    memcpy(padded_msg, message, msg_len);
    padded_msg[msg_len] = 0x80; 
    memset(padded_msg + msg_len + 1, 0, padded_len - msg_len - 1);
}
void ecb_encrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *ciphertext) {
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        dummy_block_cipher(plaintext + i, key, ciphertext + i);
    }
}
void cbc_encrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        xor_blocks(plaintext + i, iv, temp, BLOCK_SIZE);
        dummy_block_cipher(temp, key, ciphertext + i);
        memcpy(iv, ciphertext + i, BLOCK_SIZE); 
    }
}
void cfb_encrypt(uint8_t *plaintext, int len, uint8_t *key, uint8_t *iv, uint8_t *ciphertext) {
    uint8_t temp[BLOCK_SIZE];
    for (int i = 0; i < len; i += BLOCK_SIZE) {
        dummy_block_cipher(iv, key, temp); 
        xor_blocks(plaintext + i, temp, ciphertext + i, BLOCK_SIZE);
        memcpy(iv, ciphertext + i, BLOCK_SIZE); 
    }
}
void print_data(const char *label, uint8_t *data, int len) {
    printf("%s: ", label);
    for (int i = 0; i < len; i++) {
        printf("%02X ", data[i]);
    }
    printf("\n");
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x90, 0xAB, 0xCD, 0xEF};
    uint8_t iv[BLOCK_SIZE] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77};
    uint8_t plaintext[] = "Hello, Modes!"; 
    int plaintext_len = sizeof(plaintext) - 1;

    int padded_len = ((plaintext_len / BLOCK_SIZE) + 1) * BLOCK_SIZE;
    uint8_t padded_plaintext[padded_len];
    uint8_t ciphertext[padded_len];
    uint8_t iv_copy[BLOCK_SIZE];

    pad_message(plaintext, plaintext_len, padded_plaintext, padded_len);
    print_data("Padded Plaintext", padded_plaintext, padded_len);

    ecb_encrypt(padded_plaintext, padded_len, key, ciphertext);
    print_data("ECB Ciphertext", ciphertext, padded_len);

    memcpy(iv_copy, iv, BLOCK_SIZE); 
    cbc_encrypt(padded_plaintext, padded_len, key, iv_copy, ciphertext);
    print_data("CBC Ciphertext", ciphertext, padded_len);

    memcpy(iv_copy, iv, BLOCK_SIZE); 
    cfb_encrypt(padded_plaintext, padded_len, key, iv_copy, ciphertext);
    print_data("CFB Ciphertext", ciphertext, padded_len);

    return 0;
}

