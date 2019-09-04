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
typedef  int /*<<< orphan*/  prof_tdata_t ;

/* Variables and functions */

void
prof_sample_threshold_update(prof_tdata_t *tdata) {
#ifdef JEMALLOC_PROF
	uint64_t r;
	double u;

	if (!config_prof) {
		return;
	}

	if (lg_prof_sample == 0) {
		tdata->bytes_until_sample = 0;
		return;
	}

	/*
	 * Compute sample interval as a geometrically distributed random
	 * variable with mean (2^lg_prof_sample).
	 *
	 *                             __        __
	 *                             |  log(u)  |                     1
	 * tdata->bytes_until_sample = | -------- |, where p = ---------------
	 *                             | log(1-p) |             lg_prof_sample
	 *                                                     2
	 *
	 * For more information on the math, see:
	 *
	 *   Non-Uniform Random Variate Generation
	 *   Luc Devroye
	 *   Springer-Verlag, New York, 1986
	 *   pp 500
	 *   (http://luc.devroye.org/rnbookindex.html)
	 */
	r = prng_lg_range_u64(&tdata->prng_state, 53);
	u = (double)r * (1.0/9007199254740992.0L);
	tdata->bytes_until_sample = (uint64_t)(log(u) /
	    log(1.0 - (1.0 / (double)((uint64_t)1U << lg_prof_sample))))
	    + (uint64_t)1U;
#endif
}