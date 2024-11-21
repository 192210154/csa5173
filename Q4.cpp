#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], char key[], char encryptedText[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';
            encryptedText[i] = (text[i] - offset + (key[j % keyLen] - keyOffset)) % 26 + offset;
            j++;
        } else {
            encryptedText[i] = text[i];
        }
    }
    encryptedText[textLen] = '\0';
}

void decrypt(char text[], char key[], char decryptedText[]) {
    int textLen = strlen(text);
    int keyLen = strlen(key);
    int i, j;

    for (i = 0, j = 0; i < textLen; i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            char keyOffset = isupper(key[j % keyLen]) ? 'A' : 'a';
            decryptedText[i] = (text[i] - offset - (key[j % keyLen] - keyOffset) + 26) % 26 + offset;
            j++;
        } else {
            decryptedText[i] = text[i];
        }
    }
    decryptedText[textLen] = '\0';
}

int main() {
    char text[100], key[100], result[100];
    int choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; // Remove newline character

    printf("Enter the key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Remove newline character

    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            encrypt(text, key, result);
            printf("Encrypted text: %s\n", result);
            break;
        case 2:
            decrypt(text, key, result);
            printf("Decrypted text: %s\n", result);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

