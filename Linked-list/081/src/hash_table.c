/******************************************************************************
 * @file: hash_table.c
 *
 * File conatins implementation of a hash table.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wis.edu)
 *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>

#include "ll_functions.h"
#include "ll_structs.h"

#include "hash_table.h"

size_t _hash(HT *T, size_t key) {
    size_t hash = key ^ (~HT_NUM_BUCKETS);
    for (size_t i = 0; i < 5; i++) {
        hash = (31 * hash) + 17;
    }
    return hash % HT_NUM_BUCKETS;
}

HT *HT_Init() {
    HT *ret = (HT *)malloc(sizeof(HT));
    if (!ret) 
        return NULL;

    for (size_t i = 0; i < HT_NUM_BUCKETS; i++) {
        ret->buckets[i] = LL_Init();
        if (!ret->buckets[i]) {
            for (size_t j = i - 1; j < HT_NUM_BUCKETS; j--) {
                LL_Free(ret->buckets[j]);
            }
            free(ret);
            return NULL;
        }
    }
    return ret;
}

int HT_Put(HT *T, size_t key, char *value, size_t n) {
    if (!T) 
        return 0;

    size_t hash = _hash(T, key);
    LL *bucket = T->buckets[hash];
    return LL_Insert(bucket, key, value, n);
}

int HT_Get(HT *T, size_t key, char *to_fill, size_t *n) {
    if (!T) 
        return 0;

    size_t hash = _hash(T, key);
    LL *bucket = T->buckets[hash];
    return LL_Get(bucket, key, to_fill, n);
}

void HT_Free(HT *T) {
    if (!T) 
        return;
    
    for (size_t i = 0; i < HT_NUM_BUCKETS; i++) {
        LL_Free(T->buckets[i]);
    }
    free(T);
}

