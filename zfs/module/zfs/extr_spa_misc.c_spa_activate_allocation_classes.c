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
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPA_FEATURE_ALLOCATION_CLASSES ; 
 int /*<<< orphan*/  spa_feature_incr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_feature_is_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
spa_activate_allocation_classes(spa_t *spa, dmu_tx_t *tx)
{
	/*
	 * We bump the feature refcount for each special vdev added to the pool
	 */
	ASSERT(spa_feature_is_enabled(spa, SPA_FEATURE_ALLOCATION_CLASSES));
	spa_feature_incr(spa, SPA_FEATURE_ALLOCATION_CLASSES, tx);
}