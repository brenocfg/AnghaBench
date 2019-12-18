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
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  subsdelay_heap_t ;
struct TYPE_5__ {int /*<<< orphan*/  b_check_empty; TYPE_1__* p_source; struct TYPE_5__* p_next; } ;
typedef  TYPE_2__ subsdelay_heap_entry_t ;
struct TYPE_4__ {scalar_t__ i_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int SubsdelayHeapCountOverlap( subsdelay_heap_t *p_heap, subsdelay_heap_entry_t *p_entry, vlc_tick_t i_date )
{
    int i_overlaps;

    VLC_UNUSED( p_heap );

    i_overlaps = 0;

    for( subsdelay_heap_entry_t *p_curr = p_entry->p_next; p_curr != NULL;
         p_curr = p_curr->p_next )
    {
        if( p_curr->p_source->i_start > i_date )
        {
            break;
        }

        if( !p_curr->b_check_empty ) /* subtitle was checked, and it's not empty */
        {
            i_overlaps++;
        }
    }

    return i_overlaps;
}