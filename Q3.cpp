#include <stdio.h>

#include <string.h>

#include <ctype.h>



#define SIZE 5



void generateKeyMatrix(char key[], char keyMatrix[SIZE][SIZE]) {

    int alphabet[26] = {0};

    int i, j, k = 0;



    // Mark letters used in the keyword

    for (i = 0; key[i]; i++) {

        if (key[i] == 'j') key[i] = 'i'; // Treat 'i' and 'j' as the same

        if (!alphabet[key[i] - 'a']) {

            alphabet[key[i] - 'a'] = 1;

        }

    }



    // Fill the key matrix with the keyword

    k = 0;

    for (i = 0; key[i]; i++) {

        if (alphabet[key[i] - 'a'] == 1) {

            keyMatrix[k / SIZE][k % SIZE] = key[i];

            alphabet[key[i] - 'a'] = -1; // Mark as added to the matrix

            k++;

        }

    }



    // Fill the remaining spaces with the rest of the alphabet

    for (i = 0; i < 26; i++) {

        if (i + 'a' == 'j') continue; // Skip 'j'

        if (alphabet[i] == 0) {

            keyMatrix[k / SIZE][k % SIZE] = i + 'a';

            k++;

        }

    }

}



void findPosition(char keyMatrix[SIZE][SIZE], char letter, int *row, int *col) {

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            if (keyMatrix[i][j] == letter) {

                *row = i;

                *col = j;

                return;

            }

        }

    }

}



void processPlaintext(char plaintext[], char processedText[]) {

    int len = strlen(plaintext);

    int k = 0;



    for (int i = 0; i < len; i++) {

        if (plaintext[i] == ' ') continue;



        processedText[k++] = tolower(plaintext[i] == 'j' ? 'i' : plaintext[i]);



        // Add filler 'x' if two consecutive letters are the same

        if (k > 1 && processedText[k - 1] == processedText[k - 2]) {

            processedText[k - 1] = 'x';

            processedText[k++] = tolower(plaintext[i]);

        }

    }



    // Append a filler if the length is odd

    if (k % 2 != 0) processedText[k++] = 'x';

    processedText[k] = '\0';

}



void encrypt(char plaintext[], char keyMatrix[SIZE][SIZE], char ciphertext[]) {

    int i, row1, col1, row2, col2;

    for (i = 0; plaintext[i] && plaintext[i + 1]; i += 2) {

        findPosition(keyMatrix, plaintext[i], &row1, &col1);

        findPosition(keyMatrix, plaintext[i + 1], &row2, &col2);



        if (row1 == row2) { // Same row

            ciphertext[i] = keyMatrix[row1][(col1 + 1) % SIZE];

            ciphertext[i + 1] = keyMatrix[row2][(col2 + 1) % SIZE];

        } else if (col1 == col2) { // Same column

            ciphertext[i] = keyMatrix[(row1 + 1) % SIZE][col1];

            ciphertext[i + 1] = keyMatrix[(row2 + 1) % SIZE][col2];

        } else { // Rectangle

            ciphertext[i] = keyMatrix[row1][col2];

            ciphertext[i + 1] = keyMatrix[row2][col1];

        }

    }

    ciphertext[i] = '\0';

}



int main() {

    char key[50], plaintext[100], processedText[100], ciphertext[100];

    char keyMatrix[SIZE][SIZE];



    printf("Enter the keyword: ");

    scanf("%s", key);

    for (int i = 0; key[i]; i++) key[i] = tolower(key[i]);



    generateKeyMatrix(key, keyMatrix);



    printf("Generated Key Matrix:\n");

    for (int i = 0; i < SIZE; i++) {

        for (int j = 0; j < SIZE; j++) {

            printf("%c ", keyMatrix[i][j]);

        }

        printf("\n");

    }



    printf("Enter the plaintext: ");

    scanf(" %[^\n]", plaintext);

    processPlaintext(plaintext, processedText);



    printf("Processed Plaintext: %s\n", processedText);



    encrypt(processedText, keyMatrix, ciphertext);

    printf("Ciphertext: %s\n", ciphertext);



    return 0;

}
