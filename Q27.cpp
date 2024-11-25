#include <stdio.h>
#include <stdint.h>
int mod_exp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) { 
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod;
    }
    return result;
}

int main() {
   
    int n = 3233; 
    int e = 17;   

    int plaintext_space = 26; 
    int ciphertexts[26];
    for (int i = 0; i < plaintext_space; i++) {
        ciphertexts[i] = mod_exp(i, e, n);
        printf("Plaintext: %d -> Ciphertext: %d\n", i, ciphertexts[i]);
    }

    int intercepted_ciphertext = 85;
    printf("\nIntercepted Ciphertext: %d\n", intercepted_ciphertext);

    for (int i = 0; i < plaintext_space; i++) {
        if (ciphertexts[i] == intercepted_ciphertext) {
            printf("Decrypted Plaintext: %d\n", i);
            break;
        }
    }

    return 0;
}

