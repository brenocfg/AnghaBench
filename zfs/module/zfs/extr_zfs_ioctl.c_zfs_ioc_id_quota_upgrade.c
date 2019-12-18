#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;
struct TYPE_13__ {scalar_t__ os_upgrade_id; int os_upgrade_status; TYPE_1__* os_spa; int /*<<< orphan*/  os_upgrade_lock; } ;
typedef  TYPE_3__ objset_t ;
struct TYPE_11__ {int /*<<< orphan*/  spa_upgrade_taskq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  dmu_objset_ds (TYPE_3__*) ; 
 int dmu_objset_hold_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  dmu_objset_id_quota_upgrade (TYPE_3__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (TYPE_3__*) ; 
 scalar_t__ dmu_objset_projectquota_upgradable (TYPE_3__*) ; 
 scalar_t__ dmu_objset_userobjspace_upgradable (TYPE_3__*) ; 
 int /*<<< orphan*/  dsl_dataset_rele_flags (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsl_pool_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_wait_id (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
zfs_ioc_id_quota_upgrade(zfs_cmd_t *zc)
{
	objset_t *os;
	int error;

	error = dmu_objset_hold_flags(zc->zc_name, B_TRUE, FTAG, &os);
	if (error != 0)
		return (error);

	if (dmu_objset_userobjspace_upgradable(os) ||
	    dmu_objset_projectquota_upgradable(os)) {
		mutex_enter(&os->os_upgrade_lock);
		if (os->os_upgrade_id == 0) {
			/* clear potential error code and retry */
			os->os_upgrade_status = 0;
			mutex_exit(&os->os_upgrade_lock);

			dmu_objset_id_quota_upgrade(os);
		} else {
			mutex_exit(&os->os_upgrade_lock);
		}

		dsl_pool_rele(dmu_objset_pool(os), FTAG);

		taskq_wait_id(os->os_spa->spa_upgrade_taskq, os->os_upgrade_id);
		error = os->os_upgrade_status;
	} else {
		dsl_pool_rele(dmu_objset_pool(os), FTAG);
	}

	dsl_dataset_rele_flags(dmu_objset_ds(os), DS_HOLD_FLAG_DECRYPT, FTAG);

	return (error);
}