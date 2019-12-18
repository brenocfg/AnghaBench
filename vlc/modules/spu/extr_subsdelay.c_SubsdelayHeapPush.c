#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ i_count; TYPE_3__* p_head; } ;
typedef  TYPE_2__ subsdelay_heap_t ;
struct TYPE_13__ {int b_update_ephemer; struct TYPE_13__* p_next; TYPE_1__* p_source; } ;
typedef  TYPE_3__ subsdelay_heap_entry_t ;
struct TYPE_14__ {scalar_t__ i_start; } ;
typedef  TYPE_4__ subpicture_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_11__ {scalar_t__ i_start; scalar_t__ i_stop; } ;

/* Variables and functions */
 scalar_t__ SUBSDELAY_MAX_ENTRIES ; 
 TYPE_3__* SubsdelayEntryCreate (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubsdelayRebuildList (TYPE_2__*) ; 

__attribute__((used)) static subsdelay_heap_entry_t *SubsdelayHeapPush( subsdelay_heap_t *p_heap, subpicture_t *p_subpic, filter_t *p_filter )
{
    subsdelay_heap_entry_t *p_last, *p_new_entry;

    if( p_heap->i_count >= SUBSDELAY_MAX_ENTRIES )
    {
        return NULL; /* the heap is full */
    }

    p_new_entry = SubsdelayEntryCreate( p_subpic, p_filter );

    if( !p_new_entry )
    {
        return NULL;
    }


    p_last = NULL;

    for( subsdelay_heap_entry_t *p_entry = p_heap->p_head; p_entry != NULL;
         p_entry = p_entry->p_next )
    {
        if( p_entry->p_source->i_start > p_subpic->i_start )
        {
            /* the new entry should be inserted before p_entry */
            break;
        }

        p_last = p_entry;
    }

    if( p_last )
    {
        p_new_entry->p_next = p_last->p_next;
        p_last->p_next = p_new_entry;


        if( p_last->b_update_ephemer )
        {
            /* the correct stop value can be determined */

            p_last->p_source->i_stop = p_new_entry->p_source->i_start;
            p_last->b_update_ephemer = false;
        }
    }
    else
    {
        p_new_entry->p_next = p_heap->p_head;
        p_heap->p_head = p_new_entry;
    }


    /* rebuild list */

    SubsdelayRebuildList( p_heap );

    return p_new_entry;
}