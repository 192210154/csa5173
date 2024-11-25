#include <stdio.h>
int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
int mod_inverse(int e, int phi) {
    int m0 = phi, t, q;
    int x0 = 0, x1 = 1;

    if (phi == 1)
        return 0;

    while (e > 1) {
        q = e / phi;
        t = phi;
        phi = e % phi, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    return (x1 < 0) ? x1 + m0 : x1;
}

int main() {
	
    int n = 3599;           
    int e = 31;             
    int plaintext_block = 118;

    int factor = gcd(plaintext_block, n);
    if (factor == 1 || factor == n) {
        printf("No factor found. GCD is %d, which is not helpful.\n", factor);
        return 0;
    }
    int p = factor;
    int q = n / factor;

    printf("Factors of n: p = %d, q = %d\n", p, q);

    int phi = (p - 1) * (q - 1);
    printf("phi(n) = %d\n", phi);
    int d = mod_inverse(e, phi);
    printf("Private key (d) = %d\n", d);

    return 0;
}

