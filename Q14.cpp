#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to convert a character to its position (A=0, ..., Z=25)
int charToNum(char c) {
    return tolower(c) - 'a';
}

// Function to convert a position (0-25) to a character
char numToChar(int num) {
    return 'a' + (num % 26);
}

// Function to encrypt plaintext using a one-time pad key stream
void encrypt(const char *plaintext, const int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i];
            int p = charToNum(plaintext[i]);
            ciphertext[i] = numToChar((p + shift) % 26);
        } else {
            ciphertext[i] = plaintext[i]; // Preserve spaces
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt ciphertext using a key stream
void decrypt(const char *ciphertext, const int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = key[i];
            int c = charToNum(ciphertext[i]);
            plaintext[i] = numToChar((c - shift + 26) % 26);
        } else {
            plaintext[i] = ciphertext[i]; // Preserve spaces
        }
    }
    plaintext[len] = '\0';
}
 
void findKey(const char *ciphertext, const char *desired_plaintext, int *key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int c = charToNum(ciphertext[i]);
            int p = charToNum(desired_plaintext[i]);
            key[i] = (c - p + 26) % 26;
        } else {
            key[i] = -1;  
        }
    }
}

int main() {
 
    const char *plaintext = "hi how are you";
    const int key_stream[] = {9, 0, 17, 23, 15, 21, 14, 11, 11, 2, 8, 9}; // Original key
    char ciphertext[100], decrypted[100];
 
    encrypt(plaintext, key_stream, ciphertext);
    printf("Ciphertext: %s\n", ciphertext);
 
    const char *desired_plaintext = "hi Im good'";
    int new_key[100];

    
    findKey(ciphertext, desired_plaintext, new_key);
 
    printf("New key: ");
    for (int i = 0; i < strlen(ciphertext); i++) {
        if (new_key[i] != -1) {
            printf("%d ", new_key[i]);
        }
    }
    printf("\n");
 
    decrypt(ciphertext, new_key, decrypted);
    printf("Decrypted with new key: %s\n", decrypted);

    return 0;
}
