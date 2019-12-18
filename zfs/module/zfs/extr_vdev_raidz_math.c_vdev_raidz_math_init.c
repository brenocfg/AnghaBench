#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ks_ndata; int /*<<< orphan*/ * ks_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  KSTAT_FLAG_VIRTUAL ; 
 int /*<<< orphan*/  KSTAT_TYPE_RAW ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  atomic_swap_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  benchmark_raidz () ; 
 TYPE_1__* kstat_create (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_install (TYPE_1__*) ; 
 int /*<<< orphan*/  kstat_set_raw_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raidz_math_initialized ; 
 TYPE_1__* raidz_math_kstat ; 
 int /*<<< orphan*/  raidz_math_kstat_addr ; 
 int /*<<< orphan*/  raidz_math_kstat_data ; 
 int /*<<< orphan*/  raidz_math_kstat_headers ; 
 int /*<<< orphan*/  user_sel_impl ; 
 int /*<<< orphan*/  zfs_vdev_raidz_impl ; 

void
vdev_raidz_math_init(void)
{
	/* Determine the fastest available implementation. */
	benchmark_raidz();

#if defined(_KERNEL)
	/* Install kstats for all implementations */
	raidz_math_kstat = kstat_create("zfs", 0, "vdev_raidz_bench", "misc",
	    KSTAT_TYPE_RAW, 0, KSTAT_FLAG_VIRTUAL);
	if (raidz_math_kstat != NULL) {
		raidz_math_kstat->ks_data = NULL;
		raidz_math_kstat->ks_ndata = UINT32_MAX;
		kstat_set_raw_ops(raidz_math_kstat,
		    raidz_math_kstat_headers,
		    raidz_math_kstat_data,
		    raidz_math_kstat_addr);
		kstat_install(raidz_math_kstat);
	}
#endif

	/* Finish initialization */
	atomic_swap_32(&zfs_vdev_raidz_impl, user_sel_impl);
	raidz_math_initialized = B_TRUE;
}