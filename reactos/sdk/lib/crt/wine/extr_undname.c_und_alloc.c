#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct parsed_symbol {unsigned int avail_in_first; void* alloc_list; void* (* mem_alloc_ptr ) (int) ;} ;

/* Variables and functions */
 unsigned int AVAIL_SIZE ; 
 int BLOCK_SIZE ; 
 void* stub1 (int) ; 
 void* stub2 (int) ; 

__attribute__((used)) static void*    und_alloc(struct parsed_symbol* sym, unsigned int len)
{
    void*       ptr;

#define BLOCK_SIZE      1024
#define AVAIL_SIZE      (1024 - sizeof(void*))

    if (len > AVAIL_SIZE)
    {
        /* allocate a specific block */
        ptr = sym->mem_alloc_ptr(sizeof(void*) + len);
        if (!ptr) return NULL;
        *(void**)ptr = sym->alloc_list;
        sym->alloc_list = ptr;
        sym->avail_in_first = 0;
        ptr = (char*)sym->alloc_list + sizeof(void*);
    }
    else 
    {
        if (len > sym->avail_in_first)
        {
            /* add a new block */
            ptr = sym->mem_alloc_ptr(BLOCK_SIZE);
            if (!ptr) return NULL;
            *(void**)ptr = sym->alloc_list;
            sym->alloc_list = ptr;
            sym->avail_in_first = AVAIL_SIZE;
        }
        /* grab memory from head block */
        ptr = (char*)sym->alloc_list + BLOCK_SIZE - sym->avail_in_first;
        sym->avail_in_first -= len;
    }
    return ptr;
#undef BLOCK_SIZE
#undef AVAIL_SIZE
}