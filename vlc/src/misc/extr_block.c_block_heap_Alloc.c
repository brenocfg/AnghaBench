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
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 int /*<<< orphan*/ * block_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,size_t) ; 
 int /*<<< orphan*/  block_heap_cbs ; 
 int /*<<< orphan*/  free (void*) ; 
 int /*<<< orphan*/ * malloc (int) ; 

block_t *block_heap_Alloc (void *addr, size_t length)
{
    block_t *block = malloc (sizeof (*block));
    if (block == NULL)
    {
        free (addr);
        return NULL;
    }

    return block_Init(block, &block_heap_cbs, addr, length);
}