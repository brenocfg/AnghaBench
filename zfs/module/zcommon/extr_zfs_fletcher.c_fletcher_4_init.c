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
 int /*<<< orphan*/  fletcher_4_benchmark () ; 
 int /*<<< orphan*/  fletcher_4_initialized ; 
 TYPE_1__* fletcher_4_kstat ; 
 int /*<<< orphan*/  fletcher_4_kstat_addr ; 
 int /*<<< orphan*/  fletcher_4_kstat_data ; 
 int /*<<< orphan*/  fletcher_4_kstat_headers ; 
 TYPE_1__* kstat_create (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstat_install (TYPE_1__*) ; 
 int /*<<< orphan*/  kstat_set_raw_ops (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
fletcher_4_init(void)
{
	/* Determine the fastest available implementation. */
	fletcher_4_benchmark();

#if defined(_KERNEL)
	/* Install kstats for all implementations */
	fletcher_4_kstat = kstat_create("zfs", 0, "fletcher_4_bench", "misc",
	    KSTAT_TYPE_RAW, 0, KSTAT_FLAG_VIRTUAL);
	if (fletcher_4_kstat != NULL) {
		fletcher_4_kstat->ks_data = NULL;
		fletcher_4_kstat->ks_ndata = UINT32_MAX;
		kstat_set_raw_ops(fletcher_4_kstat,
		    fletcher_4_kstat_headers,
		    fletcher_4_kstat_data,
		    fletcher_4_kstat_addr);
		kstat_install(fletcher_4_kstat);
	}
#endif

	/* Finish initialization */
	fletcher_4_initialized = B_TRUE;
}