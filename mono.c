#include <stdio.h>
#include <string.h>

void monoalphabeticCipher(char text[], char key[]) 
{
	int i;
    for ( i = 0; text[i] != '\0'; i++) {
        if (text[i] >= 'a' && text[i] <= 'z') 
            text[i] = key[text[i] - 'a'];
        else if (text[i] >= 'A' && text[i] <= 'Z') 
            text[i] = key[text[i] - 'A'] - 32; 
    }
}

int main() {
    char text[100], key[26];
    printf("Enter plaintext: ");
    gets(text);
    printf("Enter key (26 unique letters): ");
    scanf("%s", key);
    monoalphabeticCipher(text, key);
    printf("Ciphertext: %s\n", text);
    return 0;
}

