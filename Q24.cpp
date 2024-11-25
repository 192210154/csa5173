#include <stdio.h>

int gcd(int a, int b) {
    return b == 0 ? a : gcd(b, a % b);
}

int mod_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }

    return (x1 < 0) ? x1 + m0 : x1;
}

int main() {
    int p = 59, q = 61, e = 31;
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    int d = mod_inverse(e, phi);

    printf("Public Key: (e = %d, n = %d)\n", e, n);
    printf("Private Key: d = %d\n", d);

    return 0;
}

