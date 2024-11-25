#include <stdio.h>
#include <math.h>

long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
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
    long long q, a; 
    printf("Enter a prime number (q): ");
    scanf("%lld", &q);
    printf("Enter a primitive root of %lld (a): ", q);
    scanf("%lld", &a);

    long long x_A, A;
    printf("Alice, enter your private key (x_A): ");
    scanf("%lld", &x_A);
    A = mod_exp(a, x_A, q);
    printf("Alice's public key (A): %lld\n", A);

    long long x_B, B;
    printf("Bob, enter your private key (x_B): ");
    scanf("%lld", &x_B);
    B = mod_exp(a, x_B, q);
    printf("Bob's public key (B): %lld\n", B);

    long long K_A = mod_exp(B, x_A, q);
    long long K_B = mod_exp(A, x_B, q);

    printf("Shared secret key computed by Alice: %lld\n", K_A);
    printf("Shared secret key computed by Bob: %lld\n", K_B);

    if (K_A == K_B) {
        printf("Key exchange successful! Shared key: %lld\n", K_A);
    } else {
        printf("Key exchange failed.\n");
    }

    return 0;
}

