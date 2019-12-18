#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned char* state; scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ fz_arc4 ;

/* Variables and functions */

void
fz_arc4_init(fz_arc4 *arc4, const unsigned char *key, size_t keylen)
{
	unsigned int t, u;
	size_t keyindex;
	unsigned int stateindex;
	unsigned char *state;
	unsigned int counter;

	state = arc4->state;

	arc4->x = 0;
	arc4->y = 0;

	for (counter = 0; counter < 256; counter++)
	{
		state[counter] = counter;
	}

	keyindex = 0;
	stateindex = 0;

	for (counter = 0; counter < 256; counter++)
	{
		t = state[counter];
		stateindex = (stateindex + key[keyindex] + t) & 0xff;
		u = state[stateindex];

		state[stateindex] = t;
		state[counter] = u;

		if (++keyindex >= keylen)
		{
			keyindex = 0;
		}
	}
}