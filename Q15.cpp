#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define MAX_TEXT 1000

const double englishFreq[ALPHABET_SIZE] = {
    8.167, 1.492, 2.782, 4.253, 12.702, 2.228, 2.015, 6.094, 6.966,
    0.153, 0.772, 4.025, 2.406, 6.749, 7.507, 1.929, 0.095, 5.987,
    6.327, 9.056, 2.758, 0.978, 2.360, 0.150, 1.974, 0.074};


void decrypt(const char *ciphertext, char *plaintext, int key) {
    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = islower(ciphertext[i]) ? 'a' : 'A';
            plaintext[i] = (ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE + base;
        } else {
            plaintext[i] = ciphertext[i]; 
        }
    }
    plaintext[len] = '\0';
}


double calculateScore(const char *plaintext) {
    int letterCount[ALPHABET_SIZE] = {0};
    int totalLetters = 0;
    double score = 0.0;


    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            letterCount[tolower(plaintext[i]) - 'a']++;
            totalLetters++;
        }
    }

    if (totalLetters == 0) return 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        double observedFreq = (double)letterCount[i] / totalLetters * 100;
        score += (observedFreq - englishFreq[i]) * (observedFreq - englishFreq[i]);
    }

    return score;
}


void frequencyAttack(const char *ciphertext, int topN) {
    char plaintext[MAX_TEXT];
    double scores[ALPHABET_SIZE];
    int keys[ALPHABET_SIZE];


    for (int key = 0; key < ALPHABET_SIZE; key++) {
        decrypt(ciphertext, plaintext, key);
        scores[key] = calculateScore(plaintext);
        keys[key] = key;
    }

    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[i] > scores[j]) {
                double tempScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tempScore;

                int tempKey = keys[i];
                keys[i] = keys[j];
                keys[j] = tempKey;
            }
        }
    }

   
    printf("Top %d possible plaintexts:\n", topN);
    for (int i = 0; i < topN && i < ALPHABET_SIZE; i++) {
        decrypt(ciphertext, plaintext, keys[i]);
        printf("Key: %d, Score: %.2f, Plaintext: %s\n", keys[i], scores[i], plaintext);
    }
}

int main() {
    const char *ciphertext = "hello how are you";
    int topN = 10; 
    frequencyAttack(ciphertext, topN);

    return 0;
}
