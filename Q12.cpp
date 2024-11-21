#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Define matrix size
#define N 2 // Key matrix is 2x2

// Function to compute the modular inverse
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}

// Function to multiply matrices mod 26
void matrixMultiply(int res[], int mat1[], int mat2[N][N]) {
    int temp[N] = {0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            temp[i] += mat1[j] * mat2[j][i];
        }
        temp[i] %= 26;
    }
    for (int i = 0; i < N; i++) {
        res[i] = temp[i];
    }
}

// Encrypt plaintext
void hillEncrypt(const char *plaintext, char *ciphertext, int key[N][N]) {
    int len = strlen(plaintext);
    int vec[N];
    for (int i = 0; i < len; i += N) {
        // Fill vector with numerical values of current block
        for (int j = 0; j < N; j++) {
            vec[j] = (i + j < len) ? plaintext[i + j] - 'a' : 0;
        }
        // Encrypt block
        int result[N];
        matrixMultiply(result, vec, key);
        for (int j = 0; j < N; j++) {
            ciphertext[i + j] = result[j] + 'a';
        }
    }
    ciphertext[len] = '\0';
}

// Decrypt ciphertext
void hillDecrypt(const char *ciphertext, char *plaintext, int key[N][N]) {
    int determinant = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    if (determinant < 0) determinant += 26;
    int inverseDet = modInverse(determinant, 26);

    // Compute inverse key matrix
    int inverseKey[N][N] = {
        {key[1][1] * inverseDet % 26, -key[0][1] * inverseDet % 26},
        {-key[1][0] * inverseDet % 26, key[0][0] * inverseDet % 26}
    };
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (inverseKey[i][j] < 0)
                inverseKey[i][j] += 26;
        }
    }

    int len = strlen(ciphertext);
    int vec[N];
    for (int i = 0; i < len; i += N) {
        // Fill vector with numerical values of current block
        for (int j = 0; j < N; j++) {
            vec[j] = (i + j < len) ? ciphertext[i + j] - 'a' : 0;
        }
        // Decrypt block
        int result[N];
        matrixMultiply(result, vec, inverseKey);
        for (int j = 0; j < N; j++) {
            plaintext[i + j] = result[j] + 'a';
        }
    }
    plaintext[len] = '\0';
}

int main() {
   
    const char *plaintext = "hi how are you are you good?";
    char ciphertext[100], decrypted[100];

    int key[N][N] = {
        {6, 24},
        {1, 13}
    };

    printf("Plaintext: %s\n", plaintext);

    hillEncrypt(plaintext, ciphertext, key);
    printf("Ciphertext: %s\n", ciphertext);

    hillDecrypt(ciphertext, decrypted, key);
    printf("Decrypted: %s\n", decrypted);

    return 0;
}
