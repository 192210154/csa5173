#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

uint32_t simple_hash(const char *message) {
    uint32_t hash = 0;
    while (*message) {
        hash = (hash * 31) + (*message++);
    }
    return hash;
}
uint32_t generate_random_k() {
    return rand() % 10000; 
}
void dsa_sign(const char *message, uint32_t private_key, uint32_t p, uint32_t q, uint32_t g, uint32_t *r, uint32_t *s) {
    uint32_t k = generate_random_k(); 
    uint32_t hash = simple_hash(message);
    
    *r = (g ^ k) % p; 
    *s = (hash + private_key * (*r)) * k % q; 
    printf("DSA Signature: r = %u, s = %u (k = %u)\n", *r, *s, k);
}
uint32_t rsa_sign(const char *message, uint32_t private_key, uint32_t n) {
    uint32_t hash = simple_hash(message);
    return (hash ^ private_key) % n; 
}

int main() {
    srand(time(0)); 
    uint32_t p = 23, q = 11, g = 5; 
    uint32_t rsa_n = 55;
    uint32_t private_key = 7; 
    const char *message = "Hello, DSA vs RSA!";
    printf("Message: %s\n", message);

    uint32_t r1, s1, r2, s2;
    dsa_sign(message, private_key, p, q, g, &r1, &s1);
    dsa_sign(message, private_key, p, q, g, &r2, &s2);

    uint32_t rsa_signature1 = rsa_sign(message, private_key, rsa_n);
    uint32_t rsa_signature2 = rsa_sign(message, private_key, rsa_n);

    printf("\n--- Results ---\n");
    printf("DSA Signature 1: r = %u, s = %u\n", r1, s1);
    printf("DSA Signature 2: r = %u, s = %u\n", r2, s2);
    printf("RSA Signature 1: %u\n", rsa_signature1);
    printf("RSA Signature 2: %u\n", rsa_signature2);

    if (r1 != r2 || s1 != s2) {
        printf("DSA signatures differ due to random k.\n");
    } else {
        printf("DSA signatures are the same (unexpected).\n");
    }

    if (rsa_signature1 == rsa_signature2) {
        printf("RSA signatures are deterministic and the same.\n");
    } else {
        printf("RSA signatures differ (unexpected).\n");
    }

    return 0;
}

