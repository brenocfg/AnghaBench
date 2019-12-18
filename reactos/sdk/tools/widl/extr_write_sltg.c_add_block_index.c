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
struct sltg_typelib {int /*<<< orphan*/  n_file_blocks; struct sltg_block* blocks; } ;
struct sltg_block {int length; int index_string; struct sltg_block* next; void* data; } ;

/* Variables and functions */
 struct sltg_block* xmalloc (int) ; 

__attribute__((used)) static void add_block_index(struct sltg_typelib *sltg, void *data, int size, int index)
{
    struct sltg_block *block = xmalloc(sizeof(*block));

    block->length = size;
    block->data = data;
    block->index_string = index;
    block->next = NULL;

    if (sltg->blocks)
    {
        struct sltg_block *blocks = sltg->blocks;

        while (blocks->next)
            blocks = blocks->next;

        blocks->next = block;
    }
    else
        sltg->blocks = block;

    sltg->n_file_blocks++;
}