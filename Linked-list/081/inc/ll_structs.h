/******************************************************************************
 * @file: ll_structs.h
 *
 * Header file for data structures to implement a user defined linked list.
 *
 * @creator: Bujji Setty (selagamsetty@wisc.edu)
 * @modified: 11/21/21 Bujji Setty (selagamsetty@wis.edu)
 *
 *****************************************************************************/

#ifndef __LL_STRUCTS_H__
#define __LL_STRUCTS_H__

// Add whatever struct definitions you may need here

typedef struct linked_list {
    struct node_type *head;
} LL;

typedef struct node_type {
    size_t key; 
    size_t size;
    char *value;
    struct node_type *next;
}node_type;

#endif //__LL_FUNCTIONS_H__
