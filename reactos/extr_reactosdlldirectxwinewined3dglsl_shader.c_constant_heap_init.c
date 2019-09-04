#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct constant_heap {unsigned int* positions; int size; int /*<<< orphan*/ * contained; TYPE_1__* entries; } ;
struct TYPE_2__ {scalar_t__ version; } ;
typedef  unsigned int SIZE_T ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 void* heap_alloc (unsigned int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static BOOL constant_heap_init(struct constant_heap *heap, unsigned int constant_count)
{
    SIZE_T size = (constant_count + 1) * sizeof(*heap->entries)
            + constant_count * sizeof(*heap->contained)
            + constant_count * sizeof(*heap->positions);
    void *mem;

    if (!(mem = heap_alloc(size)))
    {
        ERR("Failed to allocate memory\n");
        return FALSE;
    }

    heap->entries = mem;
    heap->entries[1].version = 0;
    heap->contained = (BOOL *)(heap->entries + constant_count + 1);
    memset(heap->contained, 0, constant_count * sizeof(*heap->contained));
    heap->positions = (unsigned int *)(heap->contained + constant_count);
    heap->size = 1;

    return TRUE;
}