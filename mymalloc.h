
#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#include<stdio.h>
#include<stddef.h>

typedef struct block struct_block_t;

typedef struct_block_t* mymalloc_handler;

/**
 * @fn mymalloc_init_array()
 *
 * @brief Initialize a statically allocated array to use it as dynamic.
 *
 * @param [in] pmemory pointer to a statically declared memory space
 * @param [in] length of the memory space
 *
 * @return mymalloc_andler pointer to a struck block 
 *
 * Funtion initialize an statically allocated array to be used as a dynamic one.
 * User should statically allocate the space in memory and be shure to have the
 * corresponding W/R acces.
 * For every diferent space of memory the user wants to initialize as dinamyc a
 * handler mymalloc_andler should be declared to interact with te API.
 */
mymalloc_handler mymalloc_init_array(void *pmemory, size_t pmemory_length);

/**
 * fn mymalloc()
 *
 * @brief Allocates spaces for an object on the statically reserved mem space
 *
 * @param [in] mem_space handler of the type mymalloc_andler
 * @param [in] size the size of the space to be allocated
 *
 * The malloc function allocates space for an object whose size is specified by
 * size and whose value is indeterminate.
 */
void * mymalloc(mymalloc_handler mem_space, size_t size);

/**
 * fn myfree()
 *
 * @brief Frees spaces for an object on the statically reserved mem space
 *
 * @param [in] mem_space handler of the type mymalloc_andler
 * @param [in] size the size of the space to be allocated
 *
 * The free function causes the space pointed to by ptr to be deallocated, that
 * is, made available for further allocation.
 * If ptr is a null pointer, no action occurs. Otherwise, if the argument does
 * not match a pointer earlier returned by mymalloc, or if the space has been
 * deallocated by a call to myfree, the behavior is undefined. 
 */
void myfree(mymalloc_handler mem_space, void* ptr);

#endif

// 
// End of file.
//
