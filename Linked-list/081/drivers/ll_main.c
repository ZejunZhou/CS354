/******************************************************************************
 * @file: ll_main.c
 *
 * Main file that uses the functions in ll_fucntions.c.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wisc.edu)
 *
 * DO NOT MODIFY THE CONTENTS OF THIS FILE
 *
 *****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll_functions.h"

int main(int argc, char *argv[]) {
    // Verify command line parameters
    if(argc != 1){
        printf("expected usage: %s\n", argv[0]); 
        exit(1);
    }
    
    LL *L = LL_Init();
    if (!L) {
        printf("Error: Unable to allocate memory for Linked List!\n");
        exit(1);
    }
    if (LL_Size(L)) {
        printf("Error: Linked List just initialized but contains extra element!\n");
        exit(1);
    }
    size_t key = 42;
    size_t size = 13;
    if (LL_Get(L, key, NULL, &size)) {
        printf("Error: Get returned success with non-present key!\n");
        exit(1);
    }
    if (LL_Remove(L, key)) {
        printf("Error: Remove returned success with non-present key!\n");
        exit(1);
    }
    if (!LL_Insert(L, key, "hello", strlen("hello") + 1)) {
        printf("Error: Insert failed to write in non-present key!\n");
        exit(1);
    }

    LL_Free(L); 
    printf("Success! Make sure to check for memory leaks!\n");
    return 0;
}
