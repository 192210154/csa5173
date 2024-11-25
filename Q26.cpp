#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int gcd(int a, int b) {
    while (b != 0) {
        int t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int mod_inverse(int e, int phi) {
    int t = 0, newt = 1;
    int r = phi, newr = e;
    while (newr != 0) {
        int quotient = r / newr;
        int temp = t;
        t = newt;
        newt = temp - quotient * newt;
        temp = r;
        r = newr;
        newr = temp - quotient * newr;
    }
    if (r > 1) return -1; // No modular inverse
    if (t < 0) t += phi;
    return t;
}

void rsa_keygen(int p, int q, int *e, int *d, int *n) {
    *n = p * q;
    int phi = (p - 1) * (q - 1);

    for (*e = 2; *e < phi; (*e)++) {
        if (gcd(*e, phi) == 1) break;
    }

    *d = mod_inverse(*e, phi);
}

int rsa_encrypt(int plaintext, int e, int n) {
    int ciphertext = 1;
    for (int i = 0; i < e; i++) {
        ciphertext = (ciphertext * plaintext) % n;
    }
    return ciphertext;
}

int rsa_decrypt(int ciphertext, int d, int n) {
    int plaintext = 1;
    for (int i = 0; i < d; i++) {
        plaintext = (plaintext * ciphertext) % n;
    }
    return plaintext;
}

int main() {
    int p = 61, q = 53; 
    int e, d, n;
    rsa_keygen(p, q, &e, &d, &n);
    printf("Original keys:\n");
    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d): %d\n", d);

    int plaintext = 65; 
    int ciphertext = rsa_encrypt(plaintext, e, n);
    printf("\nPlaintext: %d\n", plaintext);
    printf("Ciphertext: %d\n", ciphertext);
    int decrypted = rsa_decrypt(ciphertext, d, n);
    printf("Decrypted text: %d\n", decrypted);

    int e_new, d_new;
    rsa_keygen(p, q, &e_new, &d_new, &n); 
    printf("\nAfter private key leak, regenerated keys:\n");
    printf("New public key (e', n): (%d, %d)\n", e_new, n);
    printf("New private key (d'): %d\n", d_new);

    printf("\nAttacker factors n once d is leaked and retrieves p, q.\n");
    printf("From p, q, they can compute any new keys (e', d').\n");
    printf("Thus, key regeneration with the same modulus is NOT safe.\n");

    return 0;
}

