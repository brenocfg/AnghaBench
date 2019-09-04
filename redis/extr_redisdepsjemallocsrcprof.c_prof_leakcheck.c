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
typedef  int /*<<< orphan*/  prof_cnt_t ;

/* Variables and functions */

__attribute__((used)) static void
prof_leakcheck(const prof_cnt_t *cnt_all, size_t leak_ngctx,
    const char *filename) {
#ifdef JEMALLOC_PROF
	/*
	 * Scaling is equivalent AdjustSamples() in jeprof, but the result may
	 * differ slightly from what jeprof reports, because here we scale the
	 * summary values, whereas jeprof scales each context individually and
	 * reports the sums of the scaled values.
	 */
	if (cnt_all->curbytes != 0) {
		double sample_period = (double)((uint64_t)1 << lg_prof_sample);
		double ratio = (((double)cnt_all->curbytes) /
		    (double)cnt_all->curobjs) / sample_period;
		double scale_factor = 1.0 / (1.0 - exp(-ratio));
		uint64_t curbytes = (uint64_t)round(((double)cnt_all->curbytes)
		    * scale_factor);
		uint64_t curobjs = (uint64_t)round(((double)cnt_all->curobjs) *
		    scale_factor);

		malloc_printf("<jemalloc>: Leak approximation summary: ~%"FMTu64
		    " byte%s, ~%"FMTu64" object%s, >= %zu context%s\n",
		    curbytes, (curbytes != 1) ? "s" : "", curobjs, (curobjs !=
		    1) ? "s" : "", leak_ngctx, (leak_ngctx != 1) ? "s" : "");
		malloc_printf(
		    "<jemalloc>: Run jeprof on \"%s\" for leak detail\n",
		    filename);
	}
#endif
}