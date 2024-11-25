#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 
#define COUNTER_MAX 256 

void xor_blocks(uint8_t *block1, uint8_t *block2, uint8_t *result, int size) {
    for (int i = 0; i < size; i++) {
        result[i] = block1[i] ^ block2[i];
    }
}
void sdes_encrypt(uint8_t *input, uint8_t key, uint8_t *output) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        output[i] = input[i] ^ (key & 1); 
    }
}
void ctr_encrypt(uint8_t *plaintext, uint8_t *ciphertext, uint8_t key, uint8_t *initial_counter, int blocks) {
    uint8_t counter[BLOCK_SIZE];
    uint8_t keystream[BLOCK_SIZE];

    memcpy(counter, initial_counter, BLOCK_SIZE); 

    for (int i = 0; i < blocks; i++) {
        sdes_encrypt(counter, key, keystream);
        xor_blocks(plaintext + i * BLOCK_SIZE, keystream, ciphertext + i * BLOCK_SIZE, BLOCK_SIZE);
        counter[BLOCK_SIZE - 1]++; 
    }
}
void ctr_decrypt(uint8_t *ciphertext, uint8_t *plaintext, uint8_t key, uint8_t *initial_counter, int blocks) {
    ctr_encrypt(ciphertext, plaintext, key, initial_counter, blocks); 
}

int main() {
  
    uint8_t plaintext[] = {
        0x00, 0x00, 0x00, 0x01, 
        0x00, 0x00, 0x00, 0x02, 
        0x00, 0x00, 0x00, 0x04 ,
    };
    uint8_t initial_counter[BLOCK_SIZE] = {0x00, 0x00, 0x00, 0x00}; 
    uint8_t key = 0x7D; 

    int plaintext_size = sizeof(plaintext);
    int blocks = plaintext_size / BLOCK_SIZE;

    uint8_t ciphertext[BLOCK_SIZE * blocks];
    uint8_t decryptedtext[BLOCK_SIZE * blocks];

    printf("Original Plaintext:\n");
    for (int i = 0; i < plaintext_size; i++) {
        printf("%02X ", plaintext[i]);
    }
    printf("\n");

    ctr_encrypt(plaintext, ciphertext, key, initial_counter, blocks);

    printf("Ciphertext:\n");
    for (int i = 0; i < plaintext_size; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    ctr_decrypt(ciphertext, decryptedtext, key, initial_counter, blocks);

    printf("Decrypted Plaintext:\n");
    for (int i = 0; i < plaintext_size; i++) {
        printf("%02X ", decryptedtext[i]);
    }
    printf("\n");

    return 0;
}

