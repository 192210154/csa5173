#include <stdio.h>
#include <string.h>
#include <ctype.h>

void prepareMatrix(char *key, char matrix[5][5]) {
    int visited[26] = {0};
    int row = 0, col = 0;
    visited['J' - 'A'] = 1;
    int i;
	for ( i = 0; key[i] != '\0'; i++) {
        char ch = toupper(key[i]);
        if (isalpha(ch) && !visited[ch - 'A']) {
            matrix[row][col] = ch;
            visited[ch - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    // Fill the remaining alphabet
    for (char ch = 'A'; ch <= 'Z'; ch++) {
        if (!visited[ch - 'A']) {
            matrix[row][col] = ch;
            visited[ch - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to print the 5x5 matrix
void printMatrix(char matrix[5][5]) {
    printf("\nPlayfair Cipher Matrix:\n");
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            printf("%c ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to preprocess plaintext (remove spaces and insert 'X' between repeated letters)
void preprocessPlaintext(char *plaintext) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }

    char newPlaintext[200];
    int newLen = 0;

    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            newPlaintext[newLen++] = plaintext[i];
            if (i + 1 < len && plaintext[i] == plaintext[i + 1]) {
                newPlaintext[newLen++] = 'X';
            }
        }
    }

    if (newLen % 2 != 0) {
        newPlaintext[newLen++] = 'X';
    }

    newPlaintext[newLen] = '\0';
    strcpy(plaintext, newPlaintext);
}

// Function to find the position of a character in the matrix
void findPosition(char ch, char matrix[5][5], int *row, int *col) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == ch) {
                *row = i;
                *col = j;
                return;
            }
        }
    }
}

// Function to encrypt the plaintext using the Playfair cipher
void encrypt(char *plaintext, char matrix[5][5]) {
    for (int i = 0; plaintext[i] != '\0'; i += 2) {
        int row1, col1, row2, col2;

        findPosition(plaintext[i], matrix, &row1, &col1);
        findPosition(plaintext[i + 1], matrix, &row2, &col2);

        if (row1 == row2) {
            // Same row: replace with the next column (wrap around if necessary)
            plaintext[i] = matrix[row1][(col1 + 1) % 5];
            plaintext[i + 1] = matrix[row2][(col2 + 1) % 5];
        } else if (col1 == col2) {
            // Same column: replace with the next row (wrap around if necessary)
            plaintext[i] = matrix[(row1 + 1) % 5][col1];
            plaintext[i + 1] = matrix[(row2 + 1) % 5][col2];
        } else {
            // Rectangle rule: replace with the characters in the same row, swapped columns
            plaintext[i] = matrix[row1][col2];
            plaintext[i + 1] = matrix[row2][col1];
        }
    }
}

int main() {
    char key[100], plaintext[200];
    char matrix[5][5];

    // Input the keyword
    printf("Enter the keyword: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove trailing newline

    // Input the plaintext
    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

    // Prepare the matrix
    prepareMatrix(key, matrix);

    // Print the matrix
    printMatrix(matrix);

    // Preprocess the plaintext
    preprocessPlaintext(plaintext);

    // Encrypt the plaintext
    encrypt(plaintext, matrix);

    // Output the encrypted message
    printf("\nEncrypted message: %s\n", plaintext);

    return 0;
}
