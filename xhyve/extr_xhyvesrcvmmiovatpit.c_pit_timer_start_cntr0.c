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
struct vatpit {scalar_t__ freq_sbt; struct channel* channel; } ;
struct channel {scalar_t__ initial; scalar_t__ callout_sbt; int /*<<< orphan*/  callout_arg; int /*<<< orphan*/  callout; } ;
typedef  scalar_t__ sbintime_t ;

/* Variables and functions */
 int /*<<< orphan*/  C_ABSOLUTE ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sbinuptime () ; 
 int /*<<< orphan*/  vatpit_callout_handler ; 

__attribute__((used)) static void
pit_timer_start_cntr0(struct vatpit *vatpit)
{
	struct channel *c;
	sbintime_t now, delta;

	c = &vatpit->channel[0];
	if (c->initial != 0) {
		delta = c->initial * vatpit->freq_sbt;
		c->callout_sbt = c->callout_sbt + delta;

		/*
		 * Reset 'callout_sbt' if the time that the callout
		 * was supposed to fire is more than 'c->initial'
		 * ticks in the past.
		 */
		now = sbinuptime();
		if (c->callout_sbt < now)
			c->callout_sbt = now + delta;

		callout_reset_sbt(&c->callout, c->callout_sbt,
		    0, vatpit_callout_handler, &c->callout_arg,
		    C_ABSOLUTE);
	}
}