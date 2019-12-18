#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  zd_name; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  pthread_rwlock_rdlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ztest_name_lock ; 
 int /*<<< orphan*/  ztest_snapshot_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ztest_snapshot_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ztest_dmu_snapshot_create_destroy(ztest_ds_t *zd, uint64_t id)
{
	(void) pthread_rwlock_rdlock(&ztest_name_lock);
	(void) ztest_snapshot_destroy(zd->zd_name, id);
	(void) ztest_snapshot_create(zd->zd_name, id);
	(void) pthread_rwlock_unlock(&ztest_name_lock);
}