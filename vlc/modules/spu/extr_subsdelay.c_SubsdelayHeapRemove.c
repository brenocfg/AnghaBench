#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* p_head; } ;
typedef  TYPE_1__ subsdelay_heap_t ;
struct TYPE_7__ {int /*<<< orphan*/ * p_filter; struct TYPE_7__* p_next; } ;
typedef  TYPE_2__ subsdelay_heap_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  SubsdelayRebuildList (TYPE_1__*) ; 

__attribute__((used)) static void SubsdelayHeapRemove( subsdelay_heap_t *p_heap, subsdelay_heap_entry_t *p_entry )
{
    subsdelay_heap_entry_t *p_prev;

    p_prev = NULL;

    for( subsdelay_heap_entry_t *p_curr = p_heap->p_head; p_curr != NULL;
         p_curr = p_curr->p_next )
    {
        if( p_curr == p_entry )
        {
            break;
        }

        p_prev = p_curr;
    }

    if( p_prev )
    {
        p_prev->p_next = p_entry->p_next;
    }
    else
    {
        p_heap->p_head = p_entry->p_next;
    }

    p_entry->p_filter = NULL;

    SubsdelayRebuildList( p_heap );
}