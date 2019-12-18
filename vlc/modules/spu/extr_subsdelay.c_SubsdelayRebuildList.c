#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_count; TYPE_2__** p_list; TYPE_2__* p_head; } ;
typedef  TYPE_1__ subsdelay_heap_t ;
struct TYPE_5__ {struct TYPE_5__* p_next; } ;
typedef  TYPE_2__ subsdelay_heap_entry_t ;

/* Variables and functions */

__attribute__((used)) static void SubsdelayRebuildList( subsdelay_heap_t *p_heap )
{
    int i_index;

    i_index = 0;
    for( subsdelay_heap_entry_t *p_curr = p_heap->p_head; p_curr != NULL;
         p_curr = p_curr->p_next )
    {
        p_heap->p_list[i_index] = p_curr;
        i_index++;
    }

    p_heap->i_count = i_index;
}