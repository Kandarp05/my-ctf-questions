#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>

// Encrypted assembly blob (ensure these bytes come from your encrypted assembly)
unsigned char encrypted_check[] = {
    0x42, 0xAA, 0xAA, 0xAA, 0xAA, 0xF1, 0xE2, 0x9B, 0x63, 0xE2, 0x29, 0x53, 0x8A, 0xDE, 0xA6, 0x20, 0xAE, 0xA5, 0x2E, 0x6A, 0xDE, 0xEB, 0xE2, 0x55, 0x6B, 0x41, 0x44, 0x20, 0xAE, 0xA5, 0x2E, 0x6A, 0xDF, 0x9F, 0xE2, 0x9B, 0x63, 0xE2, 0xA5, 0x1C, 0xAE, 0xA5, 0xAA, 0x62, 0x5C, 0x7A, 0x9E, 0xEE, 0xAE, 0xBD, 0x6A, 0x62, 0xA9, 0x82, 0x62, 0xE2, 0x27, 0xF9, 0xC1, 0x90, 0xAE, 0xA0, 0xDF, 0xBD, 0xE2, 0x55, 0x6B, 0xE2, 0x29, 0x53, 0x8A, 0xDF, 0x76, 0xE2, 0x27, 0x19, 0x21, 0xAA, 0xAA, 0xAA, 0x10, 0xBE, 0xAA, 0xAA, 0xAA, 0x41, 0xA6, 0xE2, 0x27, 0x19, 0x35, 0xAA, 0xAA, 0xAA, 0x10, 0x81, 0xAA, 0xAA, 0xAA, 0x12, 0xAB, 0xAA, 0xAA, 0xAA, 0x15, 0xAB, 0xAA, 0xAA, 0xAA, 0xA5, 0xAF, 0x69, 0x94, 0x91, 0x90, 0xB3, 0x32, 0x5F, 0x9D, 0x59, 0x3F, 0x6B, 0x8A, 0x4D, 0x77, 0x7A, 0xCF, 0x70, 0x73, 0xE1, 0xDA, 0x9D, 0x87, 0xFE, 0xE6, 0x39, 0xC9, 0xE8, 0x6C, 0xC4, 0x47, 0xA1, 0xFF, 0x02, 0xE9, 0xC5, 0xD8, 0xD8, 0xCF, 0xC9, 0xDE, 0x8A, 0xFA, 0xCB, 0xD9, 0xD9, 0xDD, 0xC5, 0xD8, 0xCE, 0x8B, 0x8B, 0xA0, 0xAA, 0xFD, 0xD8, 0xC5, 0xC4, 0xCD, 0x8B, 0x8A, 0xFE, 0xD8, 0xD3, 0x8A, 0xCB, 0xC4, 0xCB, 0xC6, 0xD3, 0xD0, 0xC3, 0xC4, 0xCD, 0x8A, 0xDE, 0xC2, 0xCF, 0x8A, 0xDE, 0xD8, 0xCB, 0xC4, 0xD9, 0xCC, 0xC5, 0xD8, 0xC7, 0xCB, 0xDE, 0xC3, 0xC5, 0xC4, 0xD9, 0x84, 0xA0, 0xAA
};

size_t check_size = sizeof(encrypted_check);
unsigned char encryption_key = 0xAA;  // Must match your encryption script

// Simple XOR decryption function.
void decrypt(unsigned char *data, size_t len, unsigned char key) {
    for (size_t i = 0; i < len; i++) {
        data[i] ^= key;
    }
}

typedef void (*check_func_t)(char *);

int main(void) {
    char password[256];
    printf("Enter password: ");
    if (scanf("%255s", password) != 1) {
        fprintf(stderr, "Input error.\n");
        return 1;
    }

    // Allocate executable memory for the decrypted code.
    void *exec_mem = mmap(NULL, check_size, PROT_READ | PROT_WRITE | PROT_EXEC,
                            MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (exec_mem == MAP_FAILED) {
        perror("mmap");
        exit(1);
    }

    // Copy and decrypt the blob.
    memcpy(exec_mem, encrypted_check, check_size);
    decrypt(exec_mem, check_size, encryption_key);

    // Optional: Dump the decrypted blob for verification.
    unsigned char *code = (unsigned char *)exec_mem;

    // Cast the memory to a function pointer and call it.
    check_func_t check_password = (check_func_t)exec_mem;
    check_password(password);

    return 0;
}

/*
E8 00 00 00 00 5B 48 8D 73 53 8A 07 8A 1E 38 D8 75 0C 84 C0 74 12 48 FF C7 48 FF C6 EB EC 48 8D 7B 76 E8 0B 00 00 00 C3 48 8D 7B 5A E8 01 00 00 00 C3 57 48 31 C9 48 89 FE 8A 06 3C 00 74 08 48 FF C1 48 FF C6 EB F2 B8 01 00 00 00 BF 01 00 00 00 5E 48 89 CA 0F 05 C3 53 33 63 72 33 74 00 46 4C 41 47 7B 68 69 64 64 65 6E 5F 63 68 65 63 6B 5F 73 75 63 63 65 73 73 7D 0A 00 57 72 6F 6E 67 20 70 61 73 73 77 6F 72 64 0A 00
*/

/*
E8 00 00 00 00 5B 48 8D 73 53 8A 07 8A 1E 38 D8 75 0C 84 C0 74 12 48 FF C7 48 FF C6 EB EC 48 8D 7B 76 E8 0B 00 00 00 C3 48 8D 7B 5A E8 01 00 00 00 C3 57 48 31 C9 48 89 FE 8A 06 3C 00 74 08 48 FF C1 48 FF C6 EB F2 B8 01 00 00 00 BF 01 00 00 00 5E 48 89 CA 0F 05 C3 53 33 63 72 33 74 00 46 4C 41 47 7B 68 69 64 64 65 6E 5F 63 68 65 63 6B 5F 73 75 63 63 65 73 73 7D 0A 00 57 72 6F 6E 67 20 70 61 73 73 77 6F 72 64 0A 00 
*/