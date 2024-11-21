#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 2
 
int modInverse(int a, int m) {
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
 
int determinantMod26(int mat[N][N]) {
    int det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    det = det % 26;
    if (det < 0) det += 26;
    return det;
}

// Function to calculate inverse matrix mod 26
void inverseMatrix(int mat[N][N], int inv[N][N]) {
    int det = determinantMod26(mat);
    int detInv = modInverse(det, 26);

    inv[0][0] = mat[1][1] * detInv % 26;
    inv[0][1] = -mat[0][1] * detInv % 26;
    inv[1][0] = -mat[1][0] * detInv % 26;
    inv[1][1] = mat[0][0] * detInv % 26;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (inv[i][j] < 0)
                inv[i][j] += 26;
        }
    }
}
 
void matrixMultiply(int res[N][N], int mat1[N][N], int mat2[N][N]) {
    int temp[N][N] = {0};
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            for (int k = 0; k < N; k++) {
                temp[i][j] += mat1[i][k] * mat2[k][j];
            }
            temp[i][j] %= 26;
        }
    }
    memcpy(res, temp, sizeof(temp));
}

int main() {
     
    int plaintext[N][N] = {
        {7, 4}, // 'h' and 'e' (mod 26)
        {11, 11} // 'l' and 'l' (mod 26)
    };
    int ciphertext[N][N] = {
        {13, 19}, // Encrypted 'h' and 'e' (mod 26)
        {21, 6} // Encrypted 'l' and 'l' (mod 26)
    };

    // Calculate the inverse of the plaintext matrix
    int invPlaintext[N][N];
    inverseMatrix(plaintext, invPlaintext);

    // Recover the key matrix
    int key[N][N];
    matrixMultiply(key, invPlaintext, ciphertext);

    // Print the recovered key
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", key[i][j]);
        }
        printf("\n");
    }

    return 0;
}
