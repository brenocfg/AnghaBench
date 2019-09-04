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
struct channel {int mode; int /*<<< orphan*/  status; scalar_t__ olbyte; } ;

/* Variables and functions */
 int TIMER_16BIT ; 
 int TIMER_INTTC ; 
 int TIMER_LATCH ; 
 int TIMER_MODE_MASK ; 
 int TIMER_RATEGEN ; 
 int TIMER_RW_MASK ; 
 int TIMER_SEL_MASK ; 
 int TIMER_SEL_READBACK ; 
 int TIMER_SQWAVE ; 
 int /*<<< orphan*/  TIMER_STS_NULLCNT ; 
 int TIMER_SWSTROBE ; 
 int pit_readback (struct vatpit*,int) ; 
 int /*<<< orphan*/  pit_update_counter (struct vatpit*,struct channel*,int) ; 

__attribute__((used)) static int
vatpit_update_mode(struct vatpit *vatpit, uint8_t val)
{
	struct channel *c;
	int sel, rw, mode;

	sel = val & TIMER_SEL_MASK;
	rw = val & TIMER_RW_MASK;
	mode = val & TIMER_MODE_MASK;

	if (sel == TIMER_SEL_READBACK)
		return (pit_readback(vatpit, val));

	if (rw != TIMER_LATCH && rw != TIMER_16BIT)
		return (-1);

	if (rw != TIMER_LATCH) {
		/*
		 * Counter mode is not affected when issuing a
		 * latch command.
		 */
		if (mode != TIMER_INTTC &&
		    mode != TIMER_RATEGEN &&
		    mode != TIMER_SQWAVE &&
		    mode != TIMER_SWSTROBE)
			return (-1);
	}

	c = &vatpit->channel[sel >> 6];
	if (rw == TIMER_LATCH)
		pit_update_counter(vatpit, c, true);
	else {
		c->mode = mode;
		c->olbyte = 0;	/* reset latch after reprogramming */
		c->status |= TIMER_STS_NULLCNT;
	}

	return (0);
}