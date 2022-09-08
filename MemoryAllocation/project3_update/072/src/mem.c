/******************************************************************************
 * @file: mem.c
 *
 * WISC NETID
 * CANVAS USERNAME
 * WISC ID NUMBER
 * OTHER COMMENTS FOR THE GRADER (OPTIONAL)
 *
 * @creator: YOUR PREFERED NAME (YOUR WISC EMAIL)
 * @modified: SUBMISSION DATE
 *****************************************************************************/

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "header.h"
#include "mem.h"

// Set this to 1 to enable dbgprintf  and dbgassert statements, make sure to 
// set it back to 0 before submitting!
#define DEBUG               0 
#define dbgprintf(...)      if (DEBUG) { printf(__VA_ARGS__); }
#define dbgassert(...)      if (DEBUG) { assert(__VA_ARGS__); }

/******************************************************************************
 * Helper functions
 *****************************************************************************/

// ADD ANY HELPER FUNCTIONS YOU MIGHT WRITE HERE 

/******************************************************************************
 * Global Variables
 *****************************************************************************/
void *heap_start;
size_t heap_size;
Header *First_header;
Header* Final_header;

/******************************************************************************
 * Memory Allocator functions
 *****************************************************************************/


int check_header (Header *header) {
    if (header == NULL) {
        return NULL;
    }
    //printf("the header contains is %d\n", *header);
    int free_status = *header & 0x00000001;
    //printf("free_status is %i\n",free_status);
    return free_status;
}

Header* get_next_header(Header *header){
    //printf("hello next header %d\n", *header);
    if (header == NULL) {
        //printf("header is null\n");
        return NULL;
    }

    //printf("prepare for delete 0\n");
    int header_alloc_size = *header & 0xFFFFFFFE;

    //printf("header is %d\n", header_alloc_size);

    if((size_t)(header) >= (size_t)Final_header) {  // when the header has reach the end of final header
        //printf("error header is greater than final header\n");
        return NULL;
    }
    
    if((header_alloc_size % 16) != 0){ //check whether allocate
       //printf("the allocate size is not mutiple of 16\n");
        return NULL;  // if the header is allocated, return null
    }
    
    
    return (Header*)((size_t)header + header_alloc_size); // current header's address + size it allocatos is next header's address
}

void* get_payload_pointer(Header header) {
    if (header == NULL) {
        return NULL;
    }
    return (void*)((size_t)header + 4);  //increment 4 bytes
}





/*
 * This function initializes the heap space for future calls to Mem_Alloc and 
 * Mem_Free. You may safely assume that this function is only called once in 
 * a given program.
 *
 * @param Heap_Start : A pointer to the start of the heap space
 * @param Heap_Size : The size the heap
 * @return void
 */
void Mem_Init(void *Heap_Start, size_t Heap_Size) {

    // Register the start of the heap to the global variable
    heap_start = Heap_Start;

    // Register the size of the heap to the global variable
    heap_size = Heap_Size;

    /* BEGIN MODIFYING CODE HERE */

    // (Extra Credit) Set up prologue blocks

    // (Extra Credit) Set up epilogue block

    // (Mandatory) Set up heap space

    /* Your first task is initialize the header for the heap. The heap may 
     * contain garbage values, your job is to mark the first header to denote
     * that heap can be treated as one large free block. To do so, you can use
     * the following steps:
     *
     * 1) Find the pointer that will be returned on the first call to malloc.
     *    Remember, this pointer must be aligned to a 16 byte boundary.
     * 2) Subtract sizeof(Header) bytes to get a pointer to the first header
     * 3) Set this header to the correct value. Ensure the LSB is 0 to mark
     *    the block as free.
     * 4) (Optional) if you are using footers, ensure you set the last 
     *    sizeof(Header) bytes to the same value as the header.
     */
     size_t first_malloc_address = (size_t) heap_start; // able to get the address of the heap
     size_t allocate_size = 0;
    
     while (first_malloc_address % 16 != 0) {
        first_malloc_address = first_malloc_address + 1; // enable the heap start block size 16
        allocate_size = allocate_size + 1;
     }

     size_t first_header_address = first_malloc_address - 4; // heap's header take 4 bytes
     First_header = (Header*) first_header_address;

     *First_header = heap_size - allocate_size + 4;


     Final_header = (Header*)((size_t)First_header + *First_header);

     //*Final_header = heap_size - allocate_size + 4;
     

     //int header_result = check_header(First_header);

     //printf("%d\n", header_result);

     //printf("the first header pointer is %d\n", *First_header);
     //printf("the heap is at %pn", heap_start);
     //printf("the header is at %p\n", First_header);
     //printf("the heap size is %d", heap_size);
     //printf("the allocate size is %d\n", allocate_size);
    
     /*
     while(heap_size % 16 != 0) {
        heap_size = heap_size + 1; // make the entire heap size be the mutiple of block size 16
     }
     */

     //First_header->size = heap_size; // divisiable to 16, is even number, means free
    /* END MODIFYING CODE HERE */



    
     /*
     while(heap_size % 16 != 0) {
        heap_size = heap_size + 1; // make the entire heap size be the mutiple of block size 16
     }
     */

     //First_header->size = heap_size; // divisiable to 16, is even number, means free
    /* END MODIFYING CODE HERE */
   
    /* END MODIFYING CODE HERE */
    return;
}

/*
 * This function  allows a user to request space on the heap. The type of param
 * payload is defined in mem.h and may not be changed. If param payload is ever
 * 0, this function should return NULL immediately. 
 *
 * @param payload : The number of bytes the user wants on the heap
 * @return A 16-byte aligned pointer to payload bytes on the heap on success,
 *         NULL on failure
 */

void* Mem_Alloc(Payload payload){
    // First, verify non-zero payload size
    if (payload <= 0) {
        //printf("the payload is less and equal than 0\n");
        return NULL;
    }

    if (First_header == NULL) {
        //printf("the first header is null\n");
        return NULL;
    }

    // Determine what size block is needed to satisfy this payload request.
    int temp_payload = payload;
    int block_payload_size = 0;

    while(((temp_payload + 8) % 16) != 0) { // make the block size divided by 16
        temp_payload = temp_payload + 1;  // payload + padding
    }
    block_payload_size = temp_payload + 8; // the payload with header and unused footer will allocate
    
    int padding = temp_payload - payload; // how many padding payload has increment

    
    Header *current_header = First_header;


    //unsigned heap_bottom_address = (unsigned)First_header + heap_size; // set the bottom address

    //printf("before the loop the current_header is at %d and has value %d\n", current_header, *current_header);

    while(current_header != NULL) {
        if(current_header >= Final_header){
            return NULL;
        }
        if(check_header(current_header) == 0){ // the header is 0
            if (*current_header >= block_payload_size) {
                //printf("there is a header can store payload\n");
                break;
            }
        } // when header status is free
        current_header = get_next_header(current_header);
        //printf("have found another header\n");
    }

    if(current_header == NULL){
        //printf("there is no space in heap can fit the payload block\n");
        return NULL;
    }

    if(current_header >= Final_header){
            //printf("exceed the heap: the current header is at %d and has %d, final header is at %d", current_header, *current_header, Final_header);
            return NULL;
        }

    //printf("the current header is at %d and has %d, final header is at %d", current_header, *current_header, Final_header);
    
    int entire_block_size = *current_header; // the block size the current header will allocate
    *current_header = *current_header + 1; // mark it as allocate

    int block_size_after_allocate = entire_block_size - block_payload_size; // the left size after allocate a block

    //printf("the block_size after trace is %d", block_payload_size);

    if (block_size_after_allocate >= 16){ //necessary for splitting
       if(block_payload_size >= entire_block_size) {
        //printf("if the block allocate size can not fit the choosen header\n");
        return (NULL);
       }

       Header *new_header;
       new_header = (Header*)((size_t)current_header + block_payload_size); //set the new header
       *new_header = block_size_after_allocate; // header has the previous space
       *current_header = block_payload_size; //given the current header the block size it needs
       *current_header = *current_header + 1; // mark it as allocate

       //printf("the new header is %d\n", *new_header);
       //printf("current header is %d\n", *current_header);
       //printf("the current header is at %u\n", current_header);
       //printf("the new header is at %u\n", new_header);

       void *payload_pointer;
       payload_pointer = (void*) ((size_t)current_header + 4);
       //printf("have return the payload");
       return payload_pointer;
    }else{
        if (current_header == Final_header){
            //printf("current header is equal to final header");
            *current_header = 0;
        }
        *current_header = *current_header; 
        void *payload_pointer;
        payload_pointer = (void*) ((size_t)current_header + 4);
        return payload_pointer;
    }


    




    // Remember, user pointers must be 16-byte aligned, and the minimum block
    // size is 16 bytes. 

    // Search the heap space for a free block that can satisfy the request. 
    // Search should be done in address order.
        // if found, determine in the block can be split
            // if split is possible, split block and set headers
            // else allocate directly into block
        // else retrun NULL 

    //return NULL;
}


/*
 * This function  allows a user to tell the memory allocator that they finished
 * using space that they had requested on the heap.
 *
 * @param ptr: A pointer
 * @return 0 on error, 1 on success 
 */
int Mem_Free(void *ptr) {
    // First, search through the allocated blocks to see if these ptr is indeed
    // one that was returned by a call to Mem_Alloc

    // If ptr is not in heap, return 0 immediately
    // If ptr is not after a Header, return 0 immediately
    // If the header before ptr is not allocated, return 0 immediately 

    // Free the block

    // Coalesce adjacent free blocks
    if (ptr == NULL) {
        return 0;
    }
    if(ptr < heap_start) {
        //printf("ptr is not in heap,");
        return 0;
    }
    if(ptr >= Final_header) {
        //printf("ptr is over the heap");
        return 0;
    }
    if(ptr - 4 == NULL){
        //printf("ptr is not after a header");
        return 0;
    }


    /**
    Header *ptr_header = (Header*)((size_t)ptr - 4);
    

    printf("the ptr is at %d\n", ptr);
    printf("the ptr header is at %d and has %d", ptr_header, *ptr_header);

    if(check_header(ptr_header) == 0){
        printf("the header of payload is not allocate");
        return 0;
    }

    int free_status = check_header(ptr_header);

    printf("the free status is %d", free_status);

    if(free_status == 1){// if the header is alllocated
        *ptr_header = *ptr_header - 1; //mark as not not allocated
    }

    
    
    //case when there is only one header in the heap and it is free
    
    Header *current_header = First_header;
    int one_status_count = 0;

    while(current_header != NULL) {
        if(check_header(current_header) == 0){
            current_header = get_next_header(current_header);
        }else{
            one_status_count = one_status_count + 1;
        }
    }

    printf("one status count is %d\n", one_status_count);

    if (one_status_count == 0){
        *ptr_header = heap_size;
        return 1;
    }
    **/
    
    Header *current_header = First_header;
    Header *previous_header = NULL;
    Header *after_header = NULL;

    //printf("the current header is at %d and has %d\n", current_header, *current_header);
    //printf("the ptr is at %d\n", ptr);
    //printf("get_payload_pointer return %d\n", get_payload_pointer(current_header));
    
    /**
    unsigned address1 = (unsigned)(get_payload_pointer(current_header));
    unsigned address2 = (unsigned)ptr;

    printf("address1 is %d and address2 is %d\n", address1, address2);

    if (address1 == address2){
        printf("true\n");
    }else{
        printf("false\n");
    }
    **/

    while(current_header != NULL) {
        unsigned address_current_header = (unsigned)(get_payload_pointer(current_header));
        unsigned address_ptr = (unsigned)ptr;
        if(address_current_header == address_ptr) {
            //printf("the address are equal\n");
            break;
        }
        previous_header = current_header;
        current_header = get_next_header(current_header);
    }

    if (current_header == NULL) {
        //printf("free fail to find the header of payload\n");
        return 0;
    }
    
    if (check_header(current_header) == 0) {
        //printf("the current header is already free, no need for free");
        return 0;
    }
    
    after_header = get_next_header(current_header);

    if (after_header == Final_header){
        *after_header = 0;
        //printf("after header is equal to final header\n");
    }

    //printf("the after header is %d and at %d\n", *after_header, after_header);
    //printf("the final header is at %d\n", Final_header);

    *current_header = *current_header - 1; //mark as free

    int coalesce_case = 0; // 0 means previsou and next are both allocate, no need

    if(previous_header != NULL && check_header(previous_header) == 0){
       coalesce_case = coalesce_case+1; //1 means when privous header is free need coalease
    }

    if(after_header != NULL && check_header(after_header) == 0){
        coalesce_case = coalesce_case+2; // 2 means when next header is free
    }

    // 3 means both privous and next need to take care
    //printf("the coalesce case is %d", coalesce_case);
    
    if(coalesce_case == 0) {
        return 1; //no need for coalesce
    }

    if (coalesce_case == 1) {
        *previous_header = *previous_header + *current_header;
        return 1;
    }

    if (coalesce_case == 2) {
        *current_header = *current_header + *after_header;
        return 1;
    }

    if (coalesce_case == 3) {
        *previous_header = *previous_header + *current_header + *after_header;
        return 1;
    }
    return 0;
}

