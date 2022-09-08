#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ll_functions.h"

#define SEED 0xbeefdead
#define KEYS      10000
#define BUFF_SIZE   256

int main(int argc, char *argv[]) {
    srand(SEED);
    LL *L = LL_Init();
    char buff[BUFF_SIZE];
    size_t size = 0;
    size_t num_elems = 0;
    for (size_t key = 0; key < KEYS; key++) {
        size = (rand() % (BUFF_SIZE/2)) + 5; // range is [5, 132]
        for (size_t i = 0; i < size; i++) {
            buff[i] = rand() % 256;
        }
        if (!LL_Insert(L, key, buff, size)) {
            printf("[ERROR]: Insert should've succeeded!\n");
            exit(1);
        }
        num_elems++;
        if (LL_Size(L) != num_elems) {
            printf("[ERROR]: Incorrect count on elements inserted!\n");
            exit(1);
        }
    }
    for (size_t key = 0; key < KEYS; key+=2) {
        if (!LL_Remove(L, key)) {
            printf("[ERROR]: Remove of even key should've succeeeded!\n");
            exit(1);
        }
        num_elems--;
        if (LL_Size(L) != num_elems) {
            printf("[ERROR]: Incorrect count on elements inserted!\n");
            exit(1);
        }
    }
    for (size_t key = 0; key < KEYS; key++) {
        size = (rand() % (BUFF_SIZE/4)) + 1; // range is [1, 65]
        for (size_t i = 0; i < size; i++) {
            buff[i] = rand() % 256;
        }
        if (!LL_Insert(L, key, buff, size)) {
            printf("[ERROR]: Insert should've succeeded!\n");
            exit(1);
        }
        if (key % 2 == 0)
            num_elems++;

        if (LL_Size(L) != num_elems) {
            printf("[ERROR]: Incorrect count on elements inserted!\n");
            exit(1);
        }
    }
    LL_Free(L); 
    printf("Success! Make sure to check for memory leaks!\n");
    return 0;
}