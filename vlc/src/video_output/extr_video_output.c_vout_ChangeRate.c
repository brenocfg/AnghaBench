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
struct TYPE_5__ {int display; float rate; int /*<<< orphan*/  control; int /*<<< orphan*/  dummy; } ;
typedef  TYPE_2__ vout_thread_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  vout_control_Hold (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_control_Release (int /*<<< orphan*/ *) ; 

void vout_ChangeRate(vout_thread_t *vout, float rate)
{
    vout_thread_sys_t *sys = vout->p;
    assert(!sys->dummy);
    assert(sys->display);

    vout_control_Hold(&sys->control);
    sys->rate = rate;
    vout_control_Release(&sys->control);
}