#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define BLOCK_SIZE 8 

void simple_block_cipher(uint64_t *block, uint64_t key) {
    *block ^= key; 
}
void cbc_mac(uint64_t *message, size_t num_blocks, uint64_t key, uint64_t *mac) {
    uint64_t previous_block = 0;  
    for (size_t i = 0; i < num_blocks; i++) {
        message[i] ^= previous_block; 
        simple_block_cipher(&message[i], key); 
        previous_block = message[i]; 
    }
    *mac = previous_block; 
}

int main() {
    uint64_t key = 0x1234567890ABCDEF;  
    uint64_t message[] = {0x4E616D65};  
    size_t num_blocks = 1; 
    uint64_t mac;
    cbc_mac(message, num_blocks, key, &mac);
    printf("CBC MAC for X: 0x%016lX\n", mac);
    uint64_t message_with_mac[] = {0x4E616D65, mac}; 
    size_t num_blocks_with_mac = 2;

    cbc_mac(message_with_mac, num_blocks_with_mac, key, &mac);
    printf("CBC MAC for X || XT: 0x%016lX\n", mac);

    return 0;
}

