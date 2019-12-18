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
typedef  int /*<<< orphan*/  ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_checkpoint_lock ; 
 scalar_t__ ztest_random (int) ; 
 int /*<<< orphan*/ * ztest_spa ; 
 int /*<<< orphan*/  ztest_spa_checkpoint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_spa_discard_checkpoint (int /*<<< orphan*/ *) ; 

void
ztest_spa_checkpoint_create_discard(ztest_ds_t *zd, uint64_t id)
{
	spa_t *spa = ztest_spa;

	mutex_enter(&ztest_checkpoint_lock);
	if (ztest_random(2) == 0) {
		ztest_spa_checkpoint(spa);
	} else {
		ztest_spa_discard_checkpoint(spa);
	}
	mutex_exit(&ztest_checkpoint_lock);
}