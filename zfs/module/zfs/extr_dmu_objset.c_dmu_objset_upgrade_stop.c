#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ taskqid_t ;
struct TYPE_6__ {scalar_t__ os_upgrade_id; int /*<<< orphan*/  os_upgrade_lock; TYPE_1__* os_spa; int /*<<< orphan*/  os_upgrade_exit; } ;
typedef  TYPE_2__ objset_t ;
struct TYPE_5__ {int /*<<< orphan*/  spa_dsl_pool; int /*<<< orphan*/  spa_upgrade_taskq; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  dmu_objset_ds (TYPE_2__*) ; 
 int /*<<< orphan*/  dsl_dataset_long_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ taskq_cancel_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upgrade_tag ; 

__attribute__((used)) static void
dmu_objset_upgrade_stop(objset_t *os)
{
	mutex_enter(&os->os_upgrade_lock);
	os->os_upgrade_exit = B_TRUE;
	if (os->os_upgrade_id != 0) {
		taskqid_t id = os->os_upgrade_id;

		os->os_upgrade_id = 0;
		mutex_exit(&os->os_upgrade_lock);

		if ((taskq_cancel_id(os->os_spa->spa_upgrade_taskq, id)) == 0) {
			dsl_dataset_long_rele(dmu_objset_ds(os), upgrade_tag);
		}
		txg_wait_synced(os->os_spa->spa_dsl_pool, 0);
	} else {
		mutex_exit(&os->os_upgrade_lock);
	}
}