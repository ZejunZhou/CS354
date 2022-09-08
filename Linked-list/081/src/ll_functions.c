/******************************************************************************
 * @file: ll_functions.c
 *
 * WISC NETID: zzhou443
 * CANVAS USERNAME: zejun zhou
 * WISC ID NUMBER: 9082321366
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL): zzhou443@wisc.edu
 * @modified: SUBMISSION DATE
 *****************************************************************************/

#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ll_structs.h"

#include "ll_functions.h"

// Set this to 1 to enable dbgprintf statements, make sure to set it back to 0 
// before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 
int check_malloc(node_type *node) {
    if(node == NULL){
        //printf("the malloc allocation failed");
        return 0;
    }else{
        //printf("the malloc allocation success");
        return 1;
    }

}

/******************************************************************************
 * Verificaiton functions
 *****************************************************************************/

/* 
 * This function allocates all the memory needed for created a new linked list,
 * and initializes any necessary fields of the LL struct. The implementation 
 * of this function directly depends on how you design your LL struct. 
 *
 * @return A valid pointer on success, NULL on failure
 */
LL *LL_Init() {
    LL *list;
    list= (LL *)malloc(sizeof(LL));

    if(list == NULL){
        free(list);
        return NULL;
    }
    
    list->head = NULL; // initialize the head pointer of linked list to null
    

    return list;    
}




/* 
 * Insert the (key, value) pair into the linkeded list. If a node with a key 
 * that matches the argument key, the current value stored with that key should
 * be overwrriten by the data in the value argument. Note, you will likely 
 * need to free the old memory or reallocate the amount of memory. Hint: You 
 * will likely also need to store the value of n for later use. 
 *
 * Note: Overwriting the value for an existing value is considered a success. 
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The key identifier for the data being inserted
 * @param payload A pointer to the data to write into the node
 * @param n The number of bytes that param value is valid for 
 * @return 1 on success, 0 on failure
 */
int LL_Insert(LL *L, size_t key, char *value, size_t n) {
    if (L == NULL) {
        //printf("the list failed to initialized");
        return 0;
    }
    node_type *node;
    node = (node_type *)malloc(sizeof(node_type));

    int malloc_node_check = check_malloc(node);

    if (malloc_node_check == 0){ // if malloc does not allocate any space at heap
        //printf("the node has failed to allocate during insert");
        return 0;
    }

    // initialize node with key and value, size
    node->key = key;


    node->value = (char*)malloc(n);
    
    if (node->value == NULL){
        //printf("malloc of value has failed, free everything");
        free(node);
        return 0;
    }

    for (int i = 0; i < n; i++) {
        *(node -> value + i) = *(value + i); //dereference the value's each address and assgin it to node pointer
    }
    //node->value = value;
    node->next = NULL;
    node->size = n;

    // when there is no node in linked list
    if (L->head == NULL){ // If the head is null, insert with a node
        L->head = node;
        //printf("succesfully insert when head is Null");
        return 1;
    }

    // if there is 1 node in linked list 
    /*
    if (L->head != NULL){
        if ((L->head)->next == NULL){
            

        }
    }
    */

   node_type *temp_node = L->head;

   // trace every node in the linked list
   while(temp_node != NULL){
    // when the key is overlapped with the parameter
    if(temp_node->key == key) {
        /**
        if(value == NULL) {
        printf("the paramenter value is null\n");
        free(temp_node->value);
        free(temp_node);
        free(node);
        return 0;
    } 
    **/
        free(temp_node->value);
        temp_node->value = (char*)malloc(n);
        if (temp_node->value == NULL){
            //printf("malloc has failed");
            free(node->value);
            free(temp_node);
            free(node);
            return 0;
        }
        for(int i = 0; i < n; i++){
            *(temp_node->value + i) = *(value+i);
        }
        temp_node->size = n;
        free(node->value);
        free(node);
        //printf("successfully insert when key duplicate");
        return 1;

    }else if (temp_node->next == NULL){
        temp_node->next = node; // insert at the last when key does not match
        //printf("successfully insert when key does not exist in list");
        return 1;
    }
    temp_node = temp_node->next; // keep trace the loop
   }
   //printf("insert has failed");
   return 0;
}

/* 
 * Getter function to return the size of the linked list.
 *
 * @return The number of nodes in the linked list struct.
 */
size_t LL_Size(LL *L) {
   if (L == NULL) {
    //printf("the size of linklist is 0 because ll is null");
    return 0;
   }
   if(L->head == NULL) {
    //printf("the size of linklist is 0 because the head is null");
    return 0;
   }
   size_t total = 0;
   node_type *node = L->head;
   while(node != NULL) {
    total = total + 1;
    node = node->next;
   }
   //printf("the total size is %d", total);
   return total;
}

/* 
 * Function should fill in the to_fill argument with the bytes of the value
 * found at node whose key is equal to the key argument. If no node in the 
 * linked list has a key value equal to the key argument, no bytes should be 
 * written to the to_fill argument, and you should return 0.
 *
 * This function should detect if the value in the linked list is too large to
 * fit into the to_fill argument. In such a case, no bytes should be written,
 * and this function should return 0.
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The search key
 * @param to_fill A pointer to an externally allocated array to be filled in
 * @param n A pointer initally set to the size of to_fill and to be set to 
 *          the actual number of bytes written upon success
 * @return 1 on success, 0 on failure
 */
int LL_Get(LL *L, size_t key, char *to_fill, size_t *n) {
    if (L == NULL) {
        //printf("the list failed to initialized");
        return 0;
    }
    if (L->head == NULL) {
        //printf("the head of list is null and has no node");
        return 0 ;
    }
    node_type *temp_node = L->head;

    while (temp_node != NULL) {
        if (temp_node->key == key) {
            size_t value_size = temp_node->size;
            if (value_size > *n){
                //printf("the linked list size is too large to fit int to_fill argument");
                return 0;
            }
            for (int i = 0; i < temp_node->size; i++) {
                *(to_fill + i) = *(temp_node->value + i);
            }
            //printf("the value size is %d, n is %d\n", temp_node->size, *n);
            *n = temp_node -> size;
            return 1;
        }
      temp_node = temp_node->next; // keep trace the loop
    }

    //printf("the get has no key value paired with the parameter");

    return 0;
}

/* 
 * Function should remove a node from the liked list if the key exists in such 
 * a node. When the node is removed, all memory allocated for that node should
 * be freed. 
 *
 * @param L A pointer to a Linked List struct (may be NULL)
 * @param key The search key
 * @return 1 on successful removal, 0 on failure
 */
int LL_Remove(LL *L, size_t key) {

    if (L == NULL) {
        //printf("the list failed to initialized");
        return 0;
    }

    
    //node_type *temp_node = (node_type *)malloc(sizeof(node_type));

    // if the head is node, assign it to next and free
    
    /**
    if(temp_node == NULL) {
        free(temp_node->value);
        free(temp_node); // check malloc
        return 0;
    }
    **/

    node_type *temp_node = L->head;

    if (L->head == NULL){
        //printf("the head of list is null and has no node");
        free(temp_node);
        return 0;
    }

    if(temp_node != NULL && temp_node->key == key) {
        //printf("enter the remove");
        L->head = temp_node->next; // remove the first node

        if(L->head == NULL){//one node in list
            //printf("one node exist in list");
            free(temp_node->value);
            free(temp_node);
            return 1;
        }
        free(temp_node->value);
        free(temp_node);
        return 1;
    }

    node_type *trace_node = L->head;

    while(trace_node->next != NULL){
        if (trace_node->next->key == key) {
            temp_node = trace_node->next;
            trace_node->next = trace_node->next->next;
            free(temp_node->value);
            free(temp_node);
            //printf("the node has been removed");
            return 1;
        }
      trace_node = trace_node->next; // keep trace the loop
    }
    
    //printf("fail to remove because it can not find the key");
    return 0;
    
}

/* 
 * Function to completely free a linked list. 
 *
 * @param L A pointer to the linked list to be freed (may be NULL)
 */
void LL_Free(LL *L) {
    if (L == NULL) {
        free(L);
        //printf("the list failed to initialized");
        return;
    }
    if (L->head == NULL){
        free(L);
        //printf("the head of list is null and has no node");
        return;
    }
    node_type *temp_node = L->head;
    node_type *delete_node;

    while (temp_node != NULL) {
        delete_node = temp_node;
        temp_node = temp_node->next;
        free(delete_node->value);
        free(delete_node);
    }
    L -> head = NULL;
    free(L);
    //printf("everything has been freed");
    return;
}

