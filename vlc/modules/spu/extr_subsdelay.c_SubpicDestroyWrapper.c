#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subsdelay_heap_t ;
struct TYPE_11__ {TYPE_2__* p_filter; } ;
typedef  TYPE_3__ subsdelay_heap_entry_t ;
struct TYPE_9__ {TYPE_3__* p_sys; } ;
struct TYPE_12__ {TYPE_1__ updater; } ;
typedef  TYPE_4__ subpicture_t ;
struct TYPE_13__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_10__ {TYPE_5__* p_sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  SubsdelayEntryDestroy (TYPE_3__*) ; 
 int /*<<< orphan*/  SubsdelayHeapLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SubsdelayHeapRemove (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  SubsdelayHeapUnlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void SubpicDestroyWrapper( subpicture_t *p_subpic )
{
    subsdelay_heap_entry_t *p_entry;
    subsdelay_heap_t *p_heap;

    p_entry = p_subpic->updater.p_sys;

    if( !p_entry )
    {
        return;
    }

    if( p_entry->p_filter )
    {
        filter_sys_t *p_sys = p_entry->p_filter->p_sys;
        p_heap = &p_sys->heap;

        SubsdelayHeapLock( p_heap );
        SubsdelayHeapRemove( p_heap, p_entry );
        SubsdelayHeapUnlock( p_heap );
    }

    SubsdelayEntryDestroy( p_entry );
}