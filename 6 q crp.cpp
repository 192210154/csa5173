#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void decryptAffineCipher(char ciphertext[], int a, int b) {
    int a_inverse = modInverse(a, ALPHABET_SIZE);
    if (a_inverse == -1) {
        printf("Multiplicative inverse does not exist for a = %d.\n", a);
        return;
    }
    char plaintext[strlen(ciphertext)];
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int c = ciphertext[i] - base;
            int p = (a_inverse * (c - b + ALPHABET_SIZE)) % ALPHABET_SIZE;
            plaintext[i] = p + base;
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
    printf("Decrypted text: %s\n", plaintext);
}

int main() {
    char ciphertext[] = "B...U...";
    int x1 = 'B' - 'A';
    int x2 = 'U' - 'A';
    int y1 = 'E' - 'A';
    int y2 = 'T' - 'A';

    int a = ((y1 - y2) * modInverse((x1 - x2 + ALPHABET_SIZE) % ALPHABET_SIZE, ALPHABET_SIZE)) % ALPHABET_SIZE;
    if (a < 0) a += ALPHABET_SIZE;

    int b = (y1 - a * x1 + ALPHABET_SIZE) % ALPHABET_SIZE;

    printf("Calculated keys: a = %d, b = %d\n", a, b);

    decryptAffineCipher(ciphertext, a, b);

    return 0;
}

