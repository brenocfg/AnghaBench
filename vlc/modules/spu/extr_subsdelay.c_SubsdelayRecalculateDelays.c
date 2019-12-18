#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int b_update_stop; TYPE_2__* p_source; scalar_t__ i_new_stop; int /*<<< orphan*/  b_update_ephemer; struct TYPE_12__* p_next; } ;
typedef  TYPE_3__ subsdelay_heap_entry_t ;
struct TYPE_13__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_10__ {TYPE_3__* p_head; } ;
struct TYPE_14__ {TYPE_1__ heap; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_11__ {scalar_t__ i_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SubsdelayEnforceDelayRules (TYPE_4__*) ; 
 scalar_t__ SubsdelayEstimateDelay (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static void SubsdelayRecalculateDelays( filter_t *p_filter )
{
    filter_sys_t *p_sys = p_filter->p_sys;
    for( subsdelay_heap_entry_t *p_curr = p_sys->heap.p_head;
         p_curr != NULL; p_curr = p_curr->p_next )
    {
        if( !p_curr->b_update_ephemer )
        {
            p_curr->i_new_stop = p_curr->p_source->i_start + SubsdelayEstimateDelay( p_filter, p_curr );
            p_curr->b_update_stop = false;
        }
    }

    SubsdelayEnforceDelayRules( p_filter );
}