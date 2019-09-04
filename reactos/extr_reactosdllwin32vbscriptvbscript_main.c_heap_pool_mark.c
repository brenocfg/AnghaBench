#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ mark; } ;
typedef  TYPE_1__ heap_pool_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 

heap_pool_t *heap_pool_mark(heap_pool_t *heap)
{
    if(heap->mark)
        return NULL;

    heap->mark = TRUE;
    return heap;
}