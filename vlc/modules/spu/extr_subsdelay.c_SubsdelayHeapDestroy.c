#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  lock; TYPE_4__* p_head; } ;
typedef  TYPE_3__ subsdelay_heap_t ;
struct TYPE_11__ {int /*<<< orphan*/ * p_filter; TYPE_2__* p_source; TYPE_1__* p_subpic; struct TYPE_11__* p_next; } ;
typedef  TYPE_4__ subsdelay_heap_entry_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_stop; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_stop; } ;

/* Variables and functions */
 int /*<<< orphan*/  SubsdelayHeapLock (TYPE_3__*) ; 
 int /*<<< orphan*/  SubsdelayHeapUnlock (TYPE_3__*) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SubsdelayHeapDestroy( subsdelay_heap_t *p_heap )
{
    SubsdelayHeapLock( p_heap );

    for( subsdelay_heap_entry_t *p_entry = p_heap->p_head;
         p_entry != NULL; p_entry = p_entry->p_next )
    {
        p_entry->p_subpic->i_stop = p_entry->p_source->i_stop;

        p_entry->p_filter = NULL;
    }

    SubsdelayHeapUnlock( p_heap );

    vlc_mutex_destroy( &p_heap->lock );
}