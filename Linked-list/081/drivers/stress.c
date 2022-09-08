/******************************************************************************
 * @file: stress.c
 *
 * Main file that stresses and benchmarks the use of a  hash table.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wisc.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "hash_table.h"

#define NUM_INSERTS 10000
#define NUM_FETCHES 100000
#define SEED        0xdeadbeef

int main(void) {
    srand(SEED);

    char checker[NUM_INSERTS][10];
    for (size_t i = 0; i < NUM_INSERTS; i++) {
        for (size_t j = 0; j < 10; j++) {
            checker[i][j] = (char)(i + j);
        }
    }
    char buf[10];
    clock_t start, end;
    start = clock();
    HT *T = HT_Init();

    for (size_t i = 0; i < NUM_INSERTS; i++) {
        assert(HT_Put(T, i, "init", strlen("init") + 1));
    }
    for (size_t i = 0; i < NUM_INSERTS; i++) {
        assert(HT_Put(T, i, checker[i], 10));
    }
    size_t size = 10;
    int key;
    for (size_t i = 0; i < NUM_FETCHES; i++) {
        key = rand() % (NUM_INSERTS);
        assert(0 <= key && key <= NUM_INSERTS);
        assert(HT_Get(T, key, buf, &size));
        assert(size == 10);
        for (size_t j = 0; j < 10; j++) {
            assert(checker[key][j] == buf[j]);
        }
    }
    HT_Free(T);
    end = clock();
    double elapsed = (double) (end - start) / CLOCKS_PER_SEC;
    printf("Took %f seconds!\n", elapsed);
    return 0;
}
