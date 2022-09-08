/******************************************************************************
 * @file: hash_table.h
 *
 * Header file for a hash table.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wis.edu)
 *
 *****************************************************************************/

#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include "ll_structs.h"

#define HT_NUM_BUCKETS 53

typedef struct hash_table {
    LL *buckets[HT_NUM_BUCKETS];
} HT;

HT *HT_Init();

int HT_Put(HT *T, size_t key, char *value, size_t n);

int HT_Get(HT *T, size_t key, char *to_fill, size_t *n);

void HT_Free(HT *T);

#endif //__HASH_TABLE_H__
