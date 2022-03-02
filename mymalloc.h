/**
 * \file: mymalloc.h
 *
 * \brief A general purpose dynamic memory allocation library
 *
 * \author: Federico D. Ceccarelli 
 *
 * With this library you will be able to use a statically allocated 'user
 * defined' space of memory as a dynamic one. Library provides dynamic memory
 * allocation routines for those memory spaces. 
 *
 * Do you find this project interesting or useful for your work? Please let me
 * know. \see fededc88@@gmail.com \see github.com/fededc88
 *
 * Any kind of submission are welcome!
 */

#ifndef __MYMALLOC_H__
#define __MYMALLOC_H__

#include <stdio.h>
#include <stddef.h>

/** opaque mymalloc block structure declaration */
typedef struct block struct_block_t;

/** mymalloc handler, the way the user interacts with the library */
typedef struct_block_t* mymalloc_handler;

/**
 * \brief Initialize a statically allocated array to be used dynamically.
 *
 * \param [in] pmemory pointer to a statically allocated memory space
 * \param [in] size length in bytes of the statically allocated memory space
 *
 * \return mymalloc_handler pointer to the corresponding dynamic memory space  
 *                          handler.
 *
 * Funtion initialize an statically allocated array to be used as a dynamic one.
 * User should statically allocate the space in memory and be shure to have the
 * corresponding W/R acces.
 * For every different space of memory the user wants to dynamically interact
 * with, a new mymalloc_handler handler should be declared and initialized to
 * interact with te API.
 */
mymalloc_handler mymalloc_init_array(void *pmemory, size_t size);

/**
 * \brief Dynamically Allocates memory space for an object on the statically
 * allocated memory space
 *
 * \param [in] mem_space mymalloc_handler handler corresponding to a memory
 *                       space.
 * \param [in] size the size of the space to be dynamically  allocated
 *
 * \return pointer to the allocated memory space
 *
 * The malloc function dynamically allocates memory space on the statically
 * allocated memory space for an object whose size is specified by size and
 * whose values are indeterminate.
 */
void * mymalloc(mymalloc_handler mem_space, size_t size);

/**
 * \brief Frees dymanically allocated memory space for an object on the statically
 *        reserved memory space.
 *
 * \param [in] mem_space mymalloc_handler handler corresponding to a memory
 *                       space.
 * \param [in] ptr pointer to a dinamically allocated memory space.
 *
 * The free function causes the space pointed to by ptr to be deallocated, that
 * is, mades it available for further allocation.
 * If ptr is a null pointer, no action occurs. Otherwise, if the argument does
 * not match a pointer earlier returned by mymalloc, or if the space has been
 * deallocated by a call to myfree, the behavior is undefined. 
 */
void myfree(mymalloc_handler mem_space, void* ptr);

#endif

// 
// End of file.
//
