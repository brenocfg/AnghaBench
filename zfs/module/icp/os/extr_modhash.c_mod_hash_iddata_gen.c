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
typedef  int uint_t ;

/* Variables and functions */

uint_t
mod_hash_iddata_gen(size_t nchains)
{
	uint_t kval, i, prime;

	/*
	 * Pick the first (odd) prime greater than nchains.  Make sure kval is
	 * odd (so start with nchains +1 or +2 as appropriate).
	 */
	kval = (nchains % 2 == 0) ? nchains + 1 : nchains + 2;

	for (;;) {
		prime = 1;
		for (i = 3; i * i <= kval; i += 2) {
			if (kval % i == 0)
				prime = 0;
		}
		if (prime == 1)
			break;
		kval += 2;
	}
	return (kval);
}