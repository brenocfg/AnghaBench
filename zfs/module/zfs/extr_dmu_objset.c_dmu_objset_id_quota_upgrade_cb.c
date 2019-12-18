#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  os_flags; } ;
typedef  TYPE_1__ objset_t ;
struct TYPE_12__ {void** ds_feature_activation; } ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTSUP ; 
 int /*<<< orphan*/  OBJSET_FLAG_PROJECTQUOTA_COMPLETE ; 
 int /*<<< orphan*/  OBJSET_FLAG_USEROBJACCOUNTING_COMPLETE ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 size_t SPA_FEATURE_PROJECT_QUOTA ; 
 size_t SPA_FEATURE_USEROBJ_ACCOUNTING ; 
 TYPE_10__* dmu_objset_ds (TYPE_1__*) ; 
 scalar_t__ dmu_objset_is_snapshot (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_pool (TYPE_1__*) ; 
 scalar_t__ dmu_objset_projectquota_enabled (TYPE_1__*) ; 
 scalar_t__ dmu_objset_projectquota_present (TYPE_1__*) ; 
 int dmu_objset_space_upgrade (TYPE_1__*) ; 
 scalar_t__ dmu_objset_userobjspace_present (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_objset_userobjused_enabled (TYPE_1__*) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dmu_objset_id_quota_upgrade_cb(objset_t *os)
{
	int err = 0;

	if (dmu_objset_userobjspace_present(os) &&
	    dmu_objset_projectquota_present(os))
		return (0);
	if (dmu_objset_is_snapshot(os))
		return (SET_ERROR(EINVAL));
	if (!dmu_objset_userobjused_enabled(os))
		return (SET_ERROR(ENOTSUP));
	if (!dmu_objset_projectquota_enabled(os) &&
	    dmu_objset_userobjspace_present(os))
		return (SET_ERROR(ENOTSUP));

	dmu_objset_ds(os)->ds_feature_activation[
	    SPA_FEATURE_USEROBJ_ACCOUNTING] = (void *)B_TRUE;
	if (dmu_objset_projectquota_enabled(os))
		dmu_objset_ds(os)->ds_feature_activation[
		    SPA_FEATURE_PROJECT_QUOTA] = (void *)B_TRUE;

	err = dmu_objset_space_upgrade(os);
	if (err)
		return (err);

	os->os_flags |= OBJSET_FLAG_USEROBJACCOUNTING_COMPLETE;
	if (dmu_objset_projectquota_enabled(os))
		os->os_flags |= OBJSET_FLAG_PROJECTQUOTA_COMPLETE;

	txg_wait_synced(dmu_objset_pool(os), 0);
	return (0);
}