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
struct vatpit {int freq_sbt; struct channel* channel; } ;
struct channel {int mode; int now_sbt; int initial; } ;
typedef  int sbintime_t ;

/* Variables and functions */
#define  TIMER_INTTC 128 
 int sbinuptime () ; 

__attribute__((used)) static int
vatpit_get_out(struct vatpit *vatpit, int channel)
{
	struct channel *c;
	sbintime_t delta_ticks;
	int out;

	c = &vatpit->channel[channel];

	switch (c->mode) {
	case TIMER_INTTC:
		delta_ticks = (sbinuptime() - c->now_sbt) / vatpit->freq_sbt;
		out = ((c->initial - delta_ticks) <= 0);
		break;
	default:
		out = 0;
		break;
	}

	return (out);
}