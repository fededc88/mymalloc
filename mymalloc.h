#include<stdio.h>
#include<stddef.h>

typedef struct block struct_block_t;

typedef struct_block_t* mymalloc_handler;

mymalloc_handler mymalloc_init_array(void *pmemory, size_t pmemory_length);

void * mymalloc(mymalloc_handler mem_space, size_t size);

void myfree(mymalloc_handler mem_space, void* ptr);
