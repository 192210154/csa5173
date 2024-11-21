#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT 1000
#define ALPHABET_SIZE 256

void countFrequency(char *text, int freq[]) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isprint(text[i])) {
            freq[(int)text[i]]++;
        }
    }
}

void displayFrequency(int freq[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (freq[i] > 0) {
            printf("Character '%c' (%d): %d occurrences\n", i, i, freq[i]);
        }
    }
}

void applySubstitution(char *text, char *mapping) {
    for (int i = 0; text[i] != '\0'; i++) {
        if (isprint(text[i]) && mapping[(int)text[i]] != '\0') {
            text[i] = mapping[(int)text[i]];
        }
    }
}

int main() {
    char ciphertext[MAX_TEXT] = "531305))6:4826)41.)41):806*;48+8560))85;;]8*;::8+83"
                                " (88)5*4:46(:88*96*7:8)(;485);5*12:*(:4956*2(54)858"
                                " 4069285);)6+8)41:1(19:480818:811:48+85;4)4851528806"
                                "*81 (19:48:(88;4(1734:48)41;161;188;12;";
    int freq[ALPHABET_SIZE] = {0};
    char mapping[ALPHABET_SIZE] = {0};

    countFrequency(ciphertext, freq);
    printf("Character Frequency Analysis:\n");
    displayFrequency(freq);

    printf("\nAssume substitutions based on frequency and context:\n");
    printf("Enter substitution pairs (ciphertext character plaintext character):\n");
    printf("(Type '0 0' to stop entering pairs)\n");
    while (1) {
        char cipher, plain;
        scanf(" %c %c", &cipher, &plain);
        if (cipher == '0' && plain == '0') break;
        mapping[(int)cipher] = plain;
    }

    applySubstitution(ciphertext, mapping);
    printf("\nDeciphered Text:\n%s\n", ciphertext);

    return 0;
}

