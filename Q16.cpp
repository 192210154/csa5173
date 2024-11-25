#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TEXT_LENGTH 1000
#define TOP_N_PLAINTEXTS 10
#define ALPHABET_SIZE 26

typedef struct {
    char letter;
    int frequency;
} Frequency;

void computeFrequency(const char *text, Frequency freq[]) {
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        freq[i].letter = 'A' + i;
        freq[i].frequency = 0;
    }
    for (int i = 0; text[i] != '\0'; i++) {
        if (isalpha(text[i])) {
            freq[toupper(text[i]) - 'A'].frequency++;
        }
    }
}

int compareFrequency(const void *a, const void *b) {
    return ((Frequency *)b)->frequency - ((Frequency *)a)->frequency;
}

void generatePlaintexts(const char *ciphertext, Frequency freq[], const char *reference, char plaintexts[][MAX_TEXT_LENGTH], int topN) {
    for (int n = 0; n < topN; n++) {
        for (int i = 0; ciphertext[i] != '\0'; i++) {
            if (isalpha(ciphertext[i])) {
                char cipherChar = toupper(ciphertext[i]);
                for (int j = 0; j < ALPHABET_SIZE; j++) {
                    if (cipherChar == freq[j].letter) {
                        plaintexts[n][i] = reference[(j + n) % ALPHABET_SIZE];
                        break;
                    }
                }
                if (islower(ciphertext[i])) {
                    plaintexts[n][i] = tolower(plaintexts[n][i]);
                }
            } else {
                plaintexts[n][i] = ciphertext[i];
            }
        }
        plaintexts[n][strlen(ciphertext)] = '\0';
    }
}

int main() {
    char ciphertext[MAX_TEXT_LENGTH];
    Frequency freq[ALPHABET_SIZE];
    char plaintexts[TOP_N_PLAINTEXTS][MAX_TEXT_LENGTH];
    const char *reference = "ETAOINSHRDLCUMWFGYPBVKJXQZ"; // Common letters in English ordered by frequency
    int topN;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character

    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &topN);
    if (topN > TOP_N_PLAINTEXTS) {
        topN = TOP_N_PLAINTEXTS;
    }

    computeFrequency(ciphertext, freq);
    qsort(freq, ALPHABET_SIZE, sizeof(Frequency), compareFrequency);

    generatePlaintexts(ciphertext, freq, reference, plaintexts, topN);

    printf("\nTop %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN; i++) {
        printf("%d: %s\n", i + 1, plaintexts[i]);
    }

    return 0;
}

