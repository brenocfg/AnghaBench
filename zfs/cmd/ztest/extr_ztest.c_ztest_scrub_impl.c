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
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int ECKSUM ; 
 int /*<<< orphan*/  POOL_SCAN_SCRUB ; 
 scalar_t__ dsl_scan_scrubbing (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_get_dsl (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_get_errlog_size (int /*<<< orphan*/ *) ; 
 int spa_scan (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_pool_scrubbed ; 

__attribute__((used)) static int
ztest_scrub_impl(spa_t *spa)
{
	int error = spa_scan(spa, POOL_SCAN_SCRUB);
	if (error)
		return (error);

	while (dsl_scan_scrubbing(spa_get_dsl(spa)))
		txg_wait_synced(spa_get_dsl(spa), 0);

	if (spa_get_errlog_size(spa) > 0)
		return (ECKSUM);

	ztest_pool_scrubbed = B_TRUE;

	return (0);
}