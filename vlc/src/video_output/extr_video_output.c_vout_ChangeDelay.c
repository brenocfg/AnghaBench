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
struct TYPE_4__ {TYPE_2__* p; } ;
typedef  TYPE_1__ vout_thread_t ;
struct TYPE_5__ {int display; int /*<<< orphan*/  control; int /*<<< orphan*/  delay; int /*<<< orphan*/  clock; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_2__ vout_thread_sys_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vlc_clock_SetDelay (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_control_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_Release (int /*<<< orphan*/ *) ; 

void vout_ChangeDelay(vout_thread_t *vout, vlc_tick_t delay)
{
    vout_thread_sys_t *sys = vout->p;
    assert(!sys->dummy);
    assert(sys->display);

    vout_control_Hold(&sys->control);
    vlc_clock_SetDelay(sys->clock, delay);
    sys->delay = delay;
    vout_control_Release(&sys->control);
}