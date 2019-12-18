#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; } ;
struct TYPE_5__ {int /*<<< orphan*/  save_level; TYPE_2__* saved_state; TYPE_2__ state; } ;
typedef  TYPE_1__ enum_emh_data ;
typedef  TYPE_2__ EMF_dc_state ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void EMF_SaveDC( enum_emh_data *info )
{
    EMF_dc_state *state = HeapAlloc( GetProcessHeap(), 0, sizeof(*state));
    if (state)
    {
        *state = info->state;
        state->next = info->saved_state;
        info->saved_state = state;
        info->save_level++;
        TRACE("save_level %d\n", info->save_level);
    }
}