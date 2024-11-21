#include <stdio.h>
#include <string.h>
#include <ctype.h>

void encrypt(char text[], int k) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset + k) % 26 + offset;
        }
    }
}

void decrypt(char text[], int k) {
    for (int i = 0; i < strlen(text); i++) {
        if (isalpha(text[i])) {
            char offset = isupper(text[i]) ? 'A' : 'a';
            text[i] = (text[i] - offset - k + 26) % 26 + offset;
        }
    }
}

int main() {
    char text[100];
    int k;
    int choice;

    printf("Enter the text: ");
    fgets(text, sizeof(text), stdin);
    text[strcspn(text, "\n")] = '\0'; 

    printf("Enter the shift value (k): ");
    scanf("%d", &k);

    printf("Choose an option:\n1. Encrypt\n2. Decrypt\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            encrypt(text, k);
            printf("Encrypted text: %s\n", text);
            break;
        case 2:
            decrypt(text, k);
            printf("Decrypted text: %s\n", text);
            break;
        default:
            printf("Invalid choice\n");
    }

    return 0;
}

