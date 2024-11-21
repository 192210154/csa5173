#include <stdio.h>
#include <string.h>
#include <ctype.h>

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;
}

void encrypt(char text[], int a, int b, char encryptedText[]) {
    int i;
    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            encryptedText[i] = ((a * (text[i] - offset) + b) % 26) + offset;
        } else {
            encryptedText[i] = text[i];
        }
    }
    encryptedText[i] = '\0';
}

void decrypt(char text[], int a, int b, char decryptedText[]) {
    int i;
    int a_inv = modInverse(a, 26);
    if (a_inv == -1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return;
    }

    for (i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            decryptedText[i] = (a_inv * ((text[i] - offset - b + 26) % 26)) % 26 + offset;
        } else {
            decryptedText[i] = text[i];
        }
    }
    decryptedText[i] = '\0';
}

int main() {
    char text[100], result[100];
    int a, b, choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the value of 'a': ");
    scanf("%d", &a);
    printf("Enter the value of 'b': ");
    scanf("%d", &b);

    if (gcd(a, 26) != 1) {
        printf("Invalid value of 'a'. It must be coprime with 26.\n");
        return 1;
    }

    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            encrypt(text, a, b, result);
            printf("Encrypted text: %s\n", result);
            break;
        case 2:
            decrypt(text, a, b, result);
            printf("Decrypted text: %s\n", result);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

