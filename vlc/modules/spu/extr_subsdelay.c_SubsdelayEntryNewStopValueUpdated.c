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
struct TYPE_5__ {scalar_t__ i_new_stop; TYPE_1__* p_subpic; int /*<<< orphan*/  b_update_stop; } ;
typedef  TYPE_2__ subsdelay_heap_entry_t ;
struct TYPE_4__ {scalar_t__ i_stop; } ;

/* Variables and functions */
 scalar_t__ VLC_TICK_FROM_MS (int) ; 

__attribute__((used)) static void SubsdelayEntryNewStopValueUpdated( subsdelay_heap_entry_t *p_entry )
{
    if( !p_entry->b_update_stop )
    {
        p_entry->p_subpic->i_stop = p_entry->i_new_stop - VLC_TICK_FROM_MS(100); /* 0.1 sec less */
    }
}