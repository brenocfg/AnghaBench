#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ pool_scrub_cmd_t ;
typedef  int /*<<< orphan*/  dsl_scan_t ;
struct TYPE_4__ {int /*<<< orphan*/ * dp_scan; } ;
typedef  TYPE_1__ dsl_pool_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOTSUP ; 
 scalar_t__ POOL_SCRUB_NORMAL ; 
 scalar_t__ POOL_SCRUB_PAUSE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_scan_is_paused_scrub (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_scan_scrubbing (TYPE_1__*) ; 

__attribute__((used)) static int
dsl_scrub_pause_resume_check(void *arg, dmu_tx_t *tx)
{
	pool_scrub_cmd_t *cmd = arg;
	dsl_pool_t *dp = dmu_tx_pool(tx);
	dsl_scan_t *scn = dp->dp_scan;

	if (*cmd == POOL_SCRUB_PAUSE) {
		/* can't pause a scrub when there is no in-progress scrub */
		if (!dsl_scan_scrubbing(dp))
			return (SET_ERROR(ENOENT));

		/* can't pause a paused scrub */
		if (dsl_scan_is_paused_scrub(scn))
			return (SET_ERROR(EBUSY));
	} else if (*cmd != POOL_SCRUB_NORMAL) {
		return (SET_ERROR(ENOTSUP));
	}

	return (0);
}