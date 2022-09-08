/******************************************************************************
 * @file: ll_functions.h
 *
 * Header file for functions that use a user defined linked list.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wis.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/
#include <stddef.h>
#include "ll_structs.h"

#ifndef __LL_FUNCTIONS_H__
#define __LL_FUNCTIONS_H__

LL *LL_Init();

int LL_Insert(LL *L, size_t key, char *value, size_t n);

size_t LL_Size(LL *L);

int LL_Get(LL *L, size_t key, char *to_fill, size_t *n);

int LL_Remove(LL *L, size_t key);

void LL_Free(LL *L);

#endif //__LL_FUNCTIONS_H__
