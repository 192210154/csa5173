#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

void createPlayfairMatrix(const char *key, char matrix[SIZE][SIZE]) {
    int used[26] = {0};
    int idx = 0;

    for (int i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I'; // Treat J as I
        if (!used[ch - 'A']) {
            matrix[idx / SIZE][idx % SIZE] = ch;
            used[ch - 'A'] = 1;
            idx++;
        }
    }

    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (ch == 'J') continue; // Skip J
        if (!used[ch - 'A']) {
            matrix[idx / SIZE][idx % SIZE] = ch;
            used[ch - 'A'] = 1;
            idx++;
        }
    }
}

void findPosition(char matrix[SIZE][SIZE], char ch, int *row, int *col) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

void decryptPlayfair(const char *ciphertext, char matrix[SIZE][SIZE], char *plaintext) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i += 2) {
        char ch1 = toupper(ciphertext[i]);
        char ch2 = toupper(ciphertext[i + 1]);
        int row1, col1, row2, col2;

        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);

        if (row1 == row2) {
            plaintext[i] = matrix[row1][(col1 + SIZE - 1) % SIZE];
            plaintext[i + 1] = matrix[row2][(col2 + SIZE - 1) % SIZE];
        } else if (col1 == col2) {
            plaintext[i] = matrix[(row1 + SIZE - 1) % SIZE][col1];
            plaintext[i + 1] = matrix[(row2 + SIZE - 1) % SIZE][col2];
        } else {
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
    plaintext[len] = '\0';
}

int main() {
    char key[] = "PLAYFAIR";
    char matrix[SIZE][SIZE];
    char ciphertext[] = "helloworld";
    char plaintext[sizeof(ciphertext)];

    createPlayfairMatrix(key, matrix);

    printf("Playfair Key Matrix:\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }

    decryptPlayfair(ciphertext, matrix, plaintext);

    printf("\nCiphertext: %s\n", ciphertext);
    printf("Decrypted text: %s\n", plaintext);

    return 0;
}

