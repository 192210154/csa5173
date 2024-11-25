#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8

// Mock DES encryption function (replace with real DES implementation)
void desEncrypt(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i]; // Simple XOR for demonstration
    }
}

// ECB mode encryption
void ecbEncrypt(uint8_t *plaintext, uint8_t *ciphertext, int length, uint8_t *key) {
    uint8_t block[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, plaintext + i, BLOCK_SIZE);
        desEncrypt(block, key);
        memcpy(ciphertext + i, block, BLOCK_SIZE);
    }
}

// ECB mode decryption
void ecbDecrypt(uint8_t *ciphertext, uint8_t *plaintext, int length, uint8_t *key) {
    uint8_t block[BLOCK_SIZE];

    for (int i = 0; i < length; i += BLOCK_SIZE) {
        memcpy(block, ciphertext + i, BLOCK_SIZE);
        desEncrypt(block, key); // XOR again with the same key (mock DES)
        memcpy(plaintext + i, block, BLOCK_SIZE);
    }
}

int main() {
    uint8_t plaintext[] = "ertggggg"; // Example plaintext
    int length = sizeof(plaintext) - 1;
    uint8_t key[BLOCK_SIZE] = {0x01, 0x23, 0x45, 0x67, 0x89, 0xAB, 0xCD, 0xEF}; // Example key
    uint8_t ciphertext[length];
    uint8_t decryptedText[length];

    // Ensure plaintext length is a multiple of BLOCK_SIZE
    if (length % BLOCK_SIZE != 0) {
        printf("Error: Plaintext length must be a multiple of %d bytes.\n", BLOCK_SIZE);
        return 1;
    }

    // Perform ECB encryption
    ecbEncrypt(plaintext, ciphertext, length, key);

    // Print the ciphertext
    printf("Ciphertext: ");
    for (int i = 0; i < length; i++) {
        printf("%02X ", ciphertext[i]);
    }
    printf("\n");

    // Perform ECB decryption
    ecbDecrypt(ciphertext, decryptedText, length, key);

    // Print the decrypted text
    printf("Decrypted Text: %s\n", decryptedText);

    return 0;
}       
