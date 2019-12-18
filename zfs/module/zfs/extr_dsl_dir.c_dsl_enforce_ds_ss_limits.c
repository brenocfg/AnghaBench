#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ zfs_prop_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  enforce_res_t ;
struct TYPE_5__ {int /*<<< orphan*/  dd_pool; } ;
typedef  TYPE_1__ dsl_dir_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_6__ {scalar_t__ dd_head_dataset_obj; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ENFORCE_ABOVE ; 
 int /*<<< orphan*/  ENFORCE_ALWAYS ; 
 int /*<<< orphan*/  ENFORCE_NEVER ; 
 int /*<<< orphan*/  FTAG ; 
 scalar_t__ GLOBAL_ZONEID ; 
 scalar_t__ ZFS_PROP_FILESYSTEM_LIMIT ; 
 scalar_t__ ZFS_PROP_SNAPSHOT_LIMIT ; 
 scalar_t__ crgetzoneid (int /*<<< orphan*/ *) ; 
 scalar_t__ dsl_dataset_hold_obj (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_deleg_access_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* dsl_dir_phys (TYPE_1__*) ; 
 int dsl_pool_config_held (int /*<<< orphan*/ ) ; 
 scalar_t__ dsl_prop_get_ds (int /*<<< orphan*/ *,char*,int,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ secpolicy_zfs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (scalar_t__) ; 

__attribute__((used)) static enforce_res_t
dsl_enforce_ds_ss_limits(dsl_dir_t *dd, zfs_prop_t prop, cred_t *cr)
{
	enforce_res_t enforce = ENFORCE_ALWAYS;
	uint64_t obj;
	dsl_dataset_t *ds;
	uint64_t zoned;

	ASSERT(prop == ZFS_PROP_FILESYSTEM_LIMIT ||
	    prop == ZFS_PROP_SNAPSHOT_LIMIT);

#ifdef _KERNEL
	if (crgetzoneid(cr) != GLOBAL_ZONEID)
		return (ENFORCE_ALWAYS);

	if (secpolicy_zfs(cr) == 0)
		return (ENFORCE_NEVER);
#endif

	if ((obj = dsl_dir_phys(dd)->dd_head_dataset_obj) == 0)
		return (ENFORCE_ALWAYS);

	ASSERT(dsl_pool_config_held(dd->dd_pool));

	if (dsl_dataset_hold_obj(dd->dd_pool, obj, FTAG, &ds) != 0)
		return (ENFORCE_ALWAYS);

	if (dsl_prop_get_ds(ds, "zoned", 8, 1, &zoned, NULL) || zoned) {
		/* Only root can access zoned fs's from the GZ */
		enforce = ENFORCE_ALWAYS;
	} else {
		if (dsl_deleg_access_impl(ds, zfs_prop_to_name(prop), cr) == 0)
			enforce = ENFORCE_ABOVE;
	}

	dsl_dataset_rele(ds, FTAG);
	return (enforce);
}