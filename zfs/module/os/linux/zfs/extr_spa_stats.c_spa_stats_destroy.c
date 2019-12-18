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
 int /*<<< orphan*/  spa_health_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_io_history_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_iostats_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_mmp_history_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_read_history_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_tx_assign_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_txg_history_destroy (int /*<<< orphan*/ *) ; 

void
spa_stats_destroy(spa_t *spa)
{
	spa_iostats_destroy(spa);
	spa_health_destroy(spa);
	spa_tx_assign_destroy(spa);
	spa_txg_history_destroy(spa);
	spa_read_history_destroy(spa);
	spa_io_history_destroy(spa);
	spa_mmp_history_destroy(spa);
}