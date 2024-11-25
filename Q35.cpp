#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void generate_random_key(int *key, int length) {
    for (int i = 0; i < length; i++) {
        key[i] = rand() % 26;
    }
}
void encrypt(const char *plaintext, int *key, char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') { 
            ciphertext[i] = ((plaintext[i] - 'A' + key[i]) % 26) + 'A';
        } else if (plaintext[i] >= 'a' && plaintext[i] <= 'z') { 
            ciphertext[i] = ((plaintext[i] - 'a' + key[i]) % 26) + 'a';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0'; 
}
void decrypt(const char *ciphertext, int *key, char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') { 
            plaintext[i] = ((ciphertext[i] - 'A' - key[i] + 26) % 26) + 'A';
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') { 
            plaintext[i] = ((ciphertext[i] - 'a' - key[i] + 26) % 26) + 'a';
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[len] = '\0'; 
}

int main() {
    char plaintext[256];
    printf("Enter the plaintext (alphabetic characters only): ");
    fgets(plaintext, sizeof(plaintext), stdin);

    size_t len = strlen(plaintext);
    if (plaintext[len - 1] == '\n') {
        plaintext[len - 1] = '\0';
    }

    int key[len]; 
    char ciphertext[len + 1];
    char decrypted[len + 1];

    srand(time(NULL)); 
    generate_random_key(key, len);

    encrypt(plaintext, key, ciphertext);

    decrypt(ciphertext, key, decrypted);

    printf("\nGenerated Key: ");
    for (int i = 0; i < len; i++) {
        printf("%d ", key[i]);
    }
    printf("\nCiphertext: %s", ciphertext);
    printf("\nDecrypted Text: %s\n", decrypted);

    return 0;
}

