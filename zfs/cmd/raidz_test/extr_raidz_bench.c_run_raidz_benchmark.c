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

/* Variables and functions */
 int /*<<< orphan*/  bench_fini_raidz_maps () ; 
 int /*<<< orphan*/  bench_init_raidz_map () ; 
 int /*<<< orphan*/  run_gen_bench () ; 
 int /*<<< orphan*/  run_rec_bench () ; 

void
run_raidz_benchmark(void)
{
	bench_init_raidz_map();

	run_gen_bench();
	run_rec_bench();

	bench_fini_raidz_maps();
}