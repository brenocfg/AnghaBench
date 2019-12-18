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
struct TYPE_2__ {int size; int /*<<< orphan*/ * data; } ;
struct randomizer {size_t next; size_t head; size_t history; TYPE_1__ items; } ;

/* Variables and functions */
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static void
randomizer_RemoveAt(struct randomizer *r, size_t index)
{
    /*
     * 0          head                                history   next  size
     * |-----------|...................................|---------|-----|
     * |<--------->|                                   |<------------->|
     *    ordered            order irrelevant               ordered
     */

    /* update next before index may be updated */
    if (index < r->next)
        r->next--;

    if (index < r->head)
    {
        /* item was selected, keep the selected part ordered */
        memmove(&r->items.data[index],
                &r->items.data[index + 1],
                (r->head - index - 1) * sizeof(*r->items.data));
        r->head--;
        index = r->head; /* the new index to remove */
    }

    if (index < r->history)
    {
        /* this part is unordered, no need to shift all items */
        r->items.data[index] = r->items.data[r->history - 1];
        index = r->history - 1;
        r->history--;
    }

    if (index < r->items.size - 1)
    {
        /* shift the ordered history part by one */
        memmove(&r->items.data[index],
                &r->items.data[index + 1],
                (r->items.size - index - 1) * sizeof(*r->items.data));
    }

    r->items.size--;
}