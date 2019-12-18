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
struct TYPE_4__ {int /*<<< orphan*/  os_upgrade_lock; scalar_t__ os_upgrade_id; scalar_t__ os_upgrade_exit; int /*<<< orphan*/  (* os_upgrade_cb ) (TYPE_1__*) ;int /*<<< orphan*/  os_upgrade_status; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  dmu_objset_ds (TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_dataset_long_rele (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  upgrade_tag ; 

__attribute__((used)) static void
dmu_objset_upgrade_task_cb(void *data)
{
	objset_t *os = data;

	mutex_enter(&os->os_upgrade_lock);
	os->os_upgrade_status = EINTR;
	if (!os->os_upgrade_exit) {
		mutex_exit(&os->os_upgrade_lock);

		os->os_upgrade_status = os->os_upgrade_cb(os);
		mutex_enter(&os->os_upgrade_lock);
	}
	os->os_upgrade_exit = B_TRUE;
	os->os_upgrade_id = 0;
	mutex_exit(&os->os_upgrade_lock);
	dsl_dataset_long_rele(dmu_objset_ds(os), upgrade_tag);
}