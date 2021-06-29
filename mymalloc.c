#include "mymalloc.h"

/**
 * Metadata block structure
 */
struct block {
    size_t size;
    int free;
    struct block *next; 
};

/**
 * split() - Allocates a new block by splitting a free one - assumes first fit
 */
static void split(struct block *fitting_slot, size_t size)
{
    struct block *new;

    //checks there is enough space to make a split
    if( fitting_slot->size <= (size + sizeof(struct block) ))
	return;

    // Points to the remaining free data block head
    new = (struct block*) ((void*)fitting_slot + size + sizeof(struct block));

    new->size = (fitting_slot->size) - size - sizeof(struct block);
    new->free = 1;
    if( fitting_slot->next == NULL)
	new->next = NULL;
    else
	new->next = fitting_slot->next;

    // Allocates the data block
    fitting_slot->size = size;
    fitting_slot->free = 0;
    fitting_slot->next = new;

}

/**
 * merge() - join the consecutive free blocks by removing the metadata blocks 
 *           lying in between.
 */
static void merge(mymalloc_handler mem_space)
{
    struct block *curr, *prev;

    prev = mem_space->next;

    if(prev->next == NULL)
	return; // nothing to merge

    curr = prev->next;

    while((prev->next) != NULL){
	if((prev->free) && (curr->free))
	{
	    prev->size += (curr->size) + sizeof(struct block);
	    if ( curr->next == NULL)
		prev->next = NULL;
	    else 
	    {
		prev->next = curr->next;
		curr = curr->next;
	    }
	}
	else 
	{
	    prev = curr;
	    curr = curr->next;
	}
    }
}

/**
 * mymalloc_init_array() - Initialize a statically allocated array to use it as dynamic.
 */
mymalloc_handler mymalloc_init_array(void *pmemory, size_t size)
{
    struct block *head, *first_block_free;

    head = (struct block*) pmemory;

    head->size = size; 
    head->free = 0;
    head->next = pmemory + sizeof(struct block);

    first_block_free = (struct block*)head->next;

    first_block_free->size = size - sizeof(struct block);
    first_block_free->free = 1;
    first_block_free->next = NULL;

    return head;
}

/**
 * mymalloc() - Allocates spaces for an object on the statically reserved
 *              memiory space
 */
void * mymalloc(mymalloc_handler mem_space, size_t size){

    struct block *curr, *prev;
    void *result = NULL;

    // points the first block
    curr = mem_space->next;

    // find the first free block that fits
    while( ((curr->size < size) || (curr->free == 0 )) && (curr->next != NULL) )
    {
	prev = curr;
	curr = curr->next;
    }

    if (curr->free)
    {
	if (curr->size > (size + sizeof(struct block)) )
	{
	    split(curr, size);
	    result=(void*)(++curr);
	}
	else if ((curr->size) == size){
	    curr->free = 0;
	    result=(void*)(++curr);
	}

    }
    return result;
}

/**
 * myfree() - Frees spaces for an object on the statically reserved mem space
 */
void myfree (mymalloc_handler mem_space, void *ptr)
{
    struct block* curr;

    if( (ptr < ((void*)mem_space->next)) || ((((void*)mem_space)+mem_space->size) < ptr) )
	return; // Wrong ptr

    curr = (ptr - sizeof(struct block));
    curr->free=1;

    merge(mem_space);
}

// 
// End of file.
//
