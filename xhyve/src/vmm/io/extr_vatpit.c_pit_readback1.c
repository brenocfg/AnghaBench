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
typedef  int uint8_t ;
struct vatpit {struct channel* channel; } ;
struct channel {int slatched; scalar_t__ mode; int /*<<< orphan*/  status; int /*<<< orphan*/  olbyte; } ;

/* Variables and functions */
 scalar_t__ TIMER_INTTC ; 
 int TIMER_RB_LCTR ; 
 int TIMER_RB_LSTATUS ; 
 int /*<<< orphan*/  TIMER_STS_OUT ; 
 int /*<<< orphan*/  pit_update_counter (struct vatpit*,struct channel*,int) ; 
 scalar_t__ vatpit_get_out (struct vatpit*,int) ; 

__attribute__((used)) static int
pit_readback1(struct vatpit *vatpit, int channel, uint8_t cmd)
{
	struct channel *c;

	c = &vatpit->channel[channel];

	/*
	 * Latch the count/status of the timer if not already latched.
	 * N.B. that the count/status latch-select bits are active-low.
	 */
	if (!(cmd & TIMER_RB_LCTR) && !c->olbyte) {
		(void) pit_update_counter(vatpit, c, true);
	}

	if (!(cmd & TIMER_RB_LSTATUS) && !c->slatched) {
		c->slatched = true;
		/*
		 * For mode 0, see if the elapsed time is greater
		 * than the initial value - this results in the
		 * output pin being set to 1 in the status byte.
		 */
		if (c->mode == TIMER_INTTC && vatpit_get_out(vatpit, channel))
			c->status |= TIMER_STS_OUT;
		else
			c->status &= ~TIMER_STS_OUT;
	}

	return (0);
}