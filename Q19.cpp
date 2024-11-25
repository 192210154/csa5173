#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8
#define KEY_SIZE 24


void desEncrypt(uint8_t *block, uint8_t *key) {

    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i % 8]; 
    }
}

void tripleDesEncrypt(uint8_t *block, uint8_t *key) {
    uint8_t key1[8], key2[8], key3[8];
    memcpy(key1, key, 8);
    memcpy(key2, key + 8, 8);
    memcpy(key3, key + 16, 8);

    desEncrypt(block, key1);  
    desEncrypt(block, key2); 
    desEncrypt(block, key3);  
}

void cbcEncrypt(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key, uint8_t *iv) {
    uint8_t block[BLOCK_SIZE];
    uint8_t prevCipher[BLOCK_SIZE];
    memcpy(prevCipher, iv, BLOCK_SIZE);

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);

        // XOR with previous ciphertext or IV
        for (int j = 0; j < BLOCK_SIZE; j++) {
            block[j] ^= prevCipher[j];
        }

        // Encrypt the block using 3DES
        tripleDesEncrypt(block, key);

        // Copy the encrypted block to ciphertext and set as previous ciphertext
        memcpy(ciphertext + i, block, BLOCK_SIZE);
        memcpy(prevCipher, block, BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "This is a CBC test!12345678"; 
    int length = sizeof(plaintext) - 1;
    uint8_t key[KEY_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF,
                             0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01,
                             0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF, 0x01, 0x23}; 
    uint8_t iv[BLOCK_SIZE] = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC, 0xDE, 0xF0}; 
    uint8_t ciphertext[length];

    if (length % BLOCK_SIZE != 0) {
        printf("Error: Plaintext length must be a multiple of %d bytes.\n", BLOCK_SIZE);
        return 1;
    }

    cbcEncrypt(plaintext, ciphertext, length, key, iv);

    printf("Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    return 0;
}
