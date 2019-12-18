#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  spa_root_vdev; scalar_t__ spa_scan_pass_issued; scalar_t__ spa_scan_pass_exam; scalar_t__ spa_scan_pass_scrub_spent_paused; scalar_t__ spa_scan_pass_scrub_pause; scalar_t__ spa_scan_pass_start; TYPE_1__* spa_dsl_pool; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_4__ {int /*<<< orphan*/  dp_scan; } ;

/* Variables and functions */
 scalar_t__ dsl_scan_is_paused_scrub (int /*<<< orphan*/ ) ; 
 scalar_t__ gethrestime_sec () ; 
 int /*<<< orphan*/  vdev_scan_stat_init (int /*<<< orphan*/ ) ; 

void
spa_scan_stat_init(spa_t *spa)
{
	/* data not stored on disk */
	spa->spa_scan_pass_start = gethrestime_sec();
	if (dsl_scan_is_paused_scrub(spa->spa_dsl_pool->dp_scan))
		spa->spa_scan_pass_scrub_pause = spa->spa_scan_pass_start;
	else
		spa->spa_scan_pass_scrub_pause = 0;
	spa->spa_scan_pass_scrub_spent_paused = 0;
	spa->spa_scan_pass_exam = 0;
	spa->spa_scan_pass_issued = 0;
	vdev_scan_stat_init(spa->spa_root_vdev);
}