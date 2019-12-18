#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  subsdelay_heap_t ;
struct TYPE_15__ {TYPE_2__* p_subpic; } ;
typedef  TYPE_1__ subsdelay_heap_entry_t ;
struct TYPE_16__ {int b_ephemer; scalar_t__ i_start; scalar_t__ i_stop; int /*<<< orphan*/  b_subtitle; } ;
typedef  TYPE_2__ subpicture_t ;
struct TYPE_17__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ filter_t ;
struct TYPE_18__ {int /*<<< orphan*/  heap; } ;
typedef  TYPE_4__ filter_sys_t ;

/* Variables and functions */
 scalar_t__ SubpicIsEmpty (TYPE_2__*) ; 
 int /*<<< orphan*/  SubsdelayEnforceDelayRules (TYPE_3__*) ; 
 int /*<<< orphan*/  SubsdelayHeapLock (int /*<<< orphan*/ *) ; 
 TYPE_1__* SubsdelayHeapPush (int /*<<< orphan*/ *,TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  SubsdelayHeapUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  subpicture_Delete (TYPE_2__*) ; 

__attribute__((used)) static subpicture_t * SubsdelayFilter( filter_t *p_filter, subpicture_t* p_subpic )
{
    subsdelay_heap_t *p_heap;
    subsdelay_heap_entry_t *p_entry;

    if( !p_subpic->b_subtitle )
    {
        return p_subpic;
    }

    if( SubpicIsEmpty( p_subpic ) )
    {
        /* empty subtitles usually helps terminate ephemer subtitles, but this filter calculates the stop value anyway,
           so this subtitle can be dropped */

        subpicture_Delete( p_subpic );

        return NULL;
    }

    filter_sys_t *p_sys = p_filter->p_sys;
    p_heap = &p_sys->heap;

    /* add subpicture to the heap */

    SubsdelayHeapLock( p_heap );

    p_entry = SubsdelayHeapPush( p_heap, p_subpic, p_filter );
    if( !p_entry )
    {
        SubsdelayHeapUnlock( p_heap );

        msg_Err(p_filter, "Can't add subpicture to the heap");

        return p_subpic;
    }

    p_subpic = p_entry->p_subpic; /* get the local subpic */

    if( p_subpic->b_ephemer )
    {
        /* set a relativly long delay in hope that the next subtitle
           will arrive in this time and the real delay could be determined */

        p_subpic->i_stop = p_subpic->i_start + VLC_TICK_FROM_SEC(20); /* start + 20 sec */
        p_subpic->b_ephemer = false;
    }


    SubsdelayEnforceDelayRules( p_filter );

    SubsdelayHeapUnlock( p_heap );

    return p_subpic;
}