#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  os_flags; } ;
typedef  TYPE_1__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  OBJSET_FLAG_USERACCOUNTING_COMPLETE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ dmu_objset_is_snapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (TYPE_1__*) ; 
 int dmu_objset_space_upgrade (TYPE_1__*) ; 
 scalar_t__ dmu_objset_userspace_present (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_userused_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
dmu_objset_userspace_upgrade(objset_t *os)
{
	int err = 0;

	if (dmu_objset_userspace_present(os))
		return (0);
	if (dmu_objset_is_snapshot(os))
		return (SET_ERROR(EINVAL));
	if (!dmu_objset_userused_enabled(os))
		return (SET_ERROR(ENOTSUP));

	err = dmu_objset_space_upgrade(os);
	if (err)
		return (err);

	os->os_flags |= OBJSET_FLAG_USERACCOUNTING_COMPLETE;
	txg_wait_synced(dmu_objset_pool(os), 0);
	return (0);
}