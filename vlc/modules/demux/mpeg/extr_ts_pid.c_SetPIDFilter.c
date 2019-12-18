#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_1__ ts_pid_t ;
typedef  int /*<<< orphan*/  demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_FILTERED ; 
 int UpdateHWFilter (int /*<<< orphan*/ *,TYPE_1__*) ; 

int SetPIDFilter( demux_sys_t *p_sys, ts_pid_t *p_pid, bool b_selected )
{
    if( b_selected )
        p_pid->i_flags |= FLAG_FILTERED;
    else
        p_pid->i_flags &= ~FLAG_FILTERED;

    return UpdateHWFilter( p_sys, p_pid );
}