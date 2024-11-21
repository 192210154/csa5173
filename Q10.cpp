#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define SIZE 5

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

void formatMessage(const char *input, char *formatted) {
    int len = strlen(input);
    int j = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(input[i])) {
            formatted[j++] = toupper(input[i]);
        }
    }

    formatted[j] = '\0';

    for (int i = 0; formatted[i] != '\0'; i += 2) {
        if (formatted[i] == formatted[i + 1]) {
            memmove(&formatted[i + 1], &formatted[i], strlen(&formatted[i]) + 1);
            formatted[i + 1] = 'X';
        }
    }

    if (strlen(formatted) % 2 != 0) {
        formatted[strlen(formatted)] = 'X';
        formatted[strlen(formatted) + 1] = '\0';
    }
}

void encryptPlayfair(const char *plaintext, char matrix[SIZE][SIZE], char *ciphertext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i += 2) {
        char ch1 = plaintext[i];
        char ch2 = plaintext[i + 1];
        int row1, col1, row2, col2;

        findPosition(matrix, ch1, &row1, &col1);
        findPosition(matrix, ch2, &row2, &col2);

        if (row1 == row2) {
            ciphertext[i] = matrix[row1][(col1 + 1) % SIZE];
            ciphertext[i + 1] = matrix[row2][(col2 + 1) % SIZE];
        } else if (col1 == col2) {
            ciphertext[i] = matrix[(row1 + 1) % SIZE][col1];
            ciphertext[i + 1] = matrix[(row2 + 1) % SIZE][col2];
        } else {
            ciphertext[i] = matrix[row1][col2];
            ciphertext[i + 1] = matrix[row2][col1];
        }
    }
    ciphertext[len] = '\0';
}

int main() {
    char matrix[SIZE][SIZE] = {
        {'M', 'F', 'H', 'I', 'J'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };

    char plaintext[] = "hello how are you?";
    char formatted[100];
    char ciphertext[100];

    formatMessage(plaintext, formatted);

    printf("Formatted plaintext: %s\n", formatted);

    encryptPlayfair(formatted, matrix, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);

    return 0;
}

