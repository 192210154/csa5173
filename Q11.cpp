#include <stdio.h>
#include <math.h>


unsigned long long factorial(int n) {
    if (n == 0 || n == 1)
        return 1;
    return n * factorial(n - 1);
}

int main() {
    
    int total_letters = 25; 

    unsigned long long total_keys = factorial(total_letters);

    double log2_total_keys = log2((double)total_keys);

    unsigned long long unique_keys = total_keys / (1 << 8);
    double log2_unique_keys = log2((double)unique_keys);

    printf("Approximate power of 2 for total keys: 2^%.0f\n", log2_total_keys);
    printf("Approximate power of 2 for unique keys: 2^%.0f\n", log2_unique_keys);

    return 0;
}
