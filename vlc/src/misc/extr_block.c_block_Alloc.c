#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t i_buffer; void* p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int BLOCK_ALIGN ; 
 int BLOCK_PADDING ; 
 int /*<<< orphan*/  ENOBUFS ; 
 int /*<<< orphan*/  block_Init (TYPE_1__*,int /*<<< orphan*/ *,TYPE_1__*,size_t const) ; 
 int /*<<< orphan*/  block_generic_cbs ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* malloc (size_t const) ; 
 int /*<<< orphan*/  static_assert (int,char*) ; 
 scalar_t__ unlikely (int) ; 

block_t *block_Alloc (size_t size)
{
    if (unlikely(size >> 27))
    {
        errno = ENOBUFS;
        return NULL;
    }

    /* 2 * BLOCK_PADDING: pre + post padding */
    const size_t alloc = sizeof (block_t) + BLOCK_ALIGN + (2 * BLOCK_PADDING)
                       + size;
    if (unlikely(alloc <= size))
        return NULL;

    block_t *b = malloc (alloc);
    if (unlikely(b == NULL))
        return NULL;

    block_Init(b, &block_generic_cbs, b + 1, alloc - sizeof (*b));
    static_assert ((BLOCK_PADDING % BLOCK_ALIGN) == 0,
                   "BLOCK_PADDING must be a multiple of BLOCK_ALIGN");
    b->p_buffer += BLOCK_PADDING + BLOCK_ALIGN - 1;
    b->p_buffer = (void *)(((uintptr_t)b->p_buffer) & ~(BLOCK_ALIGN - 1));
    b->i_buffer = size;
    return b;
}