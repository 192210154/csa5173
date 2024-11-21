#include <stdio.h>

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

int main() {
    int a, b, i;
    int a_inv;
    int ciphertext[] = {1, 20};  // B, U
    int plaintext[] = {4, 19};   // E, T

    int a_values[26];
    int b_values[26];
    int count = 0;

    for (a = 1; a < 26; a++) {
        if (modInverse(a, 26) == -1) continue;  // a must be coprime with 26

        b = (ciphertext[0] - a * plaintext[0] + 26) % 26;
        if ((a * plaintext[1] + b) % 26 == ciphertext[1]) {
            a_values[count] = a;
            b_values[count] = b;
            count++;
        }
    }

    printf("Possible values for (a, b):\n");
    for (i = 0; i < count; i++) {
        printf("a = %d, b = %d\n", a_values[i], b_values[i]);
    }

    if (count > 0) {
        // Assuming first valid (a, b) pair for decryption
        a = a_values[0];
        b = b_values[0];
        a_inv = modInverse(a, 26);
        if (a_inv == -1) {
            printf("No modular inverse found for a = %d\n", a);
            return 1;
        }

        char ciphertext[] = "B U";  // Example ciphertext
        char decryptedText[100];
        int j = 0;
        for (i = 0; i < strlen(ciphertext); i++) {
            if (isalpha(ciphertext[i])) {
                char offset = isupper(ciphertext[i]) ? 'A' : 'a';
                decryptedText[j++] = (a_inv * ((ciphertext[i] - offset - b + 26) % 26)) % 26 + offset;
            } else {
                decryptedText[j++] = ciphertext[i];
            }
        }
        decryptedText[j] = '\0';

        printf("Decrypted text: %s\n", decryptedText);
    }

    return 0;
}

