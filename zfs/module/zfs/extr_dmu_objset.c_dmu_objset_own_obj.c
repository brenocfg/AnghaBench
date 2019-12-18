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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  int /*<<< orphan*/  dsl_pool_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  ds_hold_flags_t ;
typedef  int /*<<< orphan*/  dmu_objset_type_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DS_HOLD_FLAG_DECRYPT ; 
 int dmu_objset_own_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,void*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_disown (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 
 int dsl_dataset_own_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ **) ; 

int
dmu_objset_own_obj(dsl_pool_t *dp, uint64_t obj, dmu_objset_type_t type,
    boolean_t readonly, boolean_t decrypt, void *tag, objset_t **osp)
{
	dsl_dataset_t *ds;
	int err;
	ds_hold_flags_t flags = (decrypt) ? DS_HOLD_FLAG_DECRYPT : 0;

	err = dsl_dataset_own_obj(dp, obj, flags, tag, &ds);
	if (err != 0)
		return (err);

	err = dmu_objset_own_impl(ds, type, readonly, decrypt, tag, osp);
	if (err != 0) {
		dsl_dataset_disown(ds, flags, tag);
		return (err);
	}

	return (0);
}