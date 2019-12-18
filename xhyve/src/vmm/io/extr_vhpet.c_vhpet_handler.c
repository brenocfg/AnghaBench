#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct vhpet_callout_arg {int timer_num; struct vhpet* vhpet; } ;
struct vhpet {int /*<<< orphan*/  vm; TYPE_1__* timer; } ;
struct callout {int dummy; } ;
typedef  int /*<<< orphan*/  sbintime_t ;
struct TYPE_2__ {struct callout callout; } ;

/* Variables and functions */
 int /*<<< orphan*/  VHPET_LOCK (struct vhpet*) ; 
 int /*<<< orphan*/  VHPET_UNLOCK (struct vhpet*) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  callout_active (struct callout*) ; 
 int /*<<< orphan*/  callout_deactivate (struct callout*) ; 
 scalar_t__ callout_pending (struct callout*) ; 
 int /*<<< orphan*/  vhpet_counter (struct vhpet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vhpet_counter_enabled (struct vhpet*) ; 
 int /*<<< orphan*/  vhpet_start_timer (struct vhpet*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vhpet_timer_interrupt (struct vhpet*,int) ; 
 int /*<<< orphan*/  xhyve_abort (char*,void*) ; 

__attribute__((used)) static void
vhpet_handler(void *a)
{
	int n;
	uint32_t counter;
	sbintime_t now;
	struct vhpet *vhpet;
	struct callout *callout;
	struct vhpet_callout_arg *arg;

	arg = a;
	vhpet = arg->vhpet;
	n = arg->timer_num;
	callout = &vhpet->timer[n].callout;

	VM_CTR1(vhpet->vm, "hpet t%d fired", n);

	VHPET_LOCK(vhpet);

	if (callout_pending(callout))		/* callout was reset */
		goto done;

	if (!callout_active(callout))		/* callout was stopped */
		goto done;

	callout_deactivate(callout);

	if (!vhpet_counter_enabled(vhpet))
		xhyve_abort("vhpet(%p) callout with counter disabled\n", (void*)vhpet);

	counter = vhpet_counter(vhpet, &now);
	vhpet_start_timer(vhpet, n, counter, now);
	vhpet_timer_interrupt(vhpet, n);
done:
	VHPET_UNLOCK(vhpet);
	return;
}