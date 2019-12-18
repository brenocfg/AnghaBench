#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vatpit_callout_arg {size_t channel_num; struct vatpit* vatpit; } ;
struct vatpit {int /*<<< orphan*/  vm; struct channel* channel; } ;
struct callout {int dummy; } ;
struct channel {scalar_t__ mode; struct callout callout; } ;

/* Variables and functions */
 scalar_t__ TIMER_RATEGEN ; 
 int /*<<< orphan*/  VATPIT_LOCK (struct vatpit*) ; 
 int /*<<< orphan*/  VATPIT_UNLOCK (struct vatpit*) ; 
 int /*<<< orphan*/  VM_CTR1 (int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  callout_active (struct callout*) ; 
 int /*<<< orphan*/  callout_deactivate (struct callout*) ; 
 scalar_t__ callout_pending (struct callout*) ; 
 int /*<<< orphan*/  pit_timer_start_cntr0 (struct vatpit*) ; 
 int /*<<< orphan*/  vatpic_pulse_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vioapic_pulse_irq (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vatpit_callout_handler(void *a)
{
	struct vatpit_callout_arg *arg = a;
	struct vatpit *vatpit;
	struct callout *callout;
	struct channel *c;

	vatpit = arg->vatpit;
	c = &vatpit->channel[arg->channel_num];
	callout = &c->callout;

	VM_CTR1(vatpit->vm, "atpit t%d fired", arg->channel_num);

	VATPIT_LOCK(vatpit);

	if (callout_pending(callout))		/* callout was reset */
		goto done;

	if (!callout_active(callout))		/* callout was stopped */
		goto done;

	callout_deactivate(callout);

	if (c->mode == TIMER_RATEGEN) {
		pit_timer_start_cntr0(vatpit);
	}

	vatpic_pulse_irq(vatpit->vm, 0);
	vioapic_pulse_irq(vatpit->vm, 2);

done:
	VATPIT_UNLOCK(vatpit);
	return;
}