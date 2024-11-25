#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define LANES 5
#define ROUND_LIMIT 4

void sha3_permutation(unsigned long state[LANES][LANES]) {
    for (int x = 0; x < LANES; x++) {
        for (int y = 0; y < LANES; y++) {
           
            state[x][y] ^= (state[(x + 1) % LANES][y] << 1) ^ (state[(x + 4) % LANES][y] >> 1);
        }
    }
}

bool all_lanes_nonzero(unsigned long state[LANES][LANES]) {
    for (int x = 0; x < LANES; x++) {
        for (int y = 0; y < LANES; y++) {
            if (state[x][y] == 0)
                return false;
        }
    }
    return true;
}

int main() {
    unsigned long state[LANES][LANES] = {0};
    state[0][0] = 0x1; 

    printf("Initial state:\n");
    for (int x = 0; x < LANES; x++) {
        for (int y = 0; y < LANES; y++) {
            printf("%016lx ", state[x][y]); 
        }
        printf("\n");
    }

    int rounds = 0;

    while (!all_lanes_nonzero(state) && rounds < ROUND_LIMIT) {
        sha3_permutation(state); 
        rounds++;

        printf("\nState after round %d:\n", rounds);
        for (int x = 0; x < LANES; x++) {
            for (int y = 0; y < LANES; y++) {
                printf("%016lx ", state[x][y]);
            }
            printf("\n");
        }
    }

    if (all_lanes_nonzero(state)) {
        printf("\nAll lanes became nonzero after %d rounds.\n", rounds);
    } else {
        printf("\nNot all lanes became nonzero within the round limit (%d rounds).\n", ROUND_LIMIT);
    }

    return 0;
}

