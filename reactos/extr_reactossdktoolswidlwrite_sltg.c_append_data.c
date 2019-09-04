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
struct sltg_data {int size; int allocated; scalar_t__ data; } ;

/* Variables and functions */
 int max (int,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,void const*,int) ; 
 scalar_t__ xrealloc (scalar_t__,int) ; 

__attribute__((used)) static void append_data(struct sltg_data *block, const void *data, int size)
{
    int new_size = block->size + size;

    if (new_size > block->allocated)
    {
        block->allocated = max(block->allocated * 2, new_size);
        block->data = xrealloc(block->data, block->allocated);
    }

    memcpy(block->data + block->size, data, size);
    block->size = new_size;
}