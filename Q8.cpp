#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

void generateCipherSequence(const char *keyword, char *cipher) {
    int used[ALPHABET_SIZE] = {0};
    int idx = 0;

    for (int i = 0; keyword[i] != '\0'; i++) {
        char ch = toupper(keyword[i]);
        if (!used[ch - 'A']) {
            cipher[idx++] = ch;
            used[ch - 'A'] = 1;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!used[ch - 'A']) {
            cipher[idx++] = ch;
        }
    }
    cipher[idx] = '\0';
}

void encrypt(const char *plaintext, const char *cipher, char *ciphertext) {
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            ciphertext[i] = cipher[plaintext[i] - base];
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
}

void decrypt(const char *ciphertext, const char *cipher, char *plaintext) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            for (int j = 0; j < ALPHABET_SIZE; j++) {
                if (toupper(ciphertext[i]) == cipher[j]) {
                    plaintext[i] = j + base;
                    break;
                }
            }
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "hello world";
    char ciphertext[100];
    char decrypted[100];
    char cipher[ALPHABET_SIZE + 1];

    generateCipherSequence(keyword, cipher);

    printf("Generated Cipher Sequence:\n");
    printf("Plain:  abcdefghijklmnopqrstuvwxyz\n");
    printf("Cipher: %s\n\n", cipher);

    encrypt(plaintext, cipher, ciphertext);
    printf("Plaintext:  %s\n", plaintext);
    printf("Ciphertext: %s\n\n", ciphertext);

    decrypt(ciphertext, cipher, decrypted);
    printf("Decrypted text: %s\n", decrypted);

    return 0;
}

