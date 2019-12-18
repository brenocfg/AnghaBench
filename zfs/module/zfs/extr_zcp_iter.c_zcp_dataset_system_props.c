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
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int ZFS_NUM_PROPS ; 
 int ZFS_PROP_TYPE ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prop_valid_for_ds (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int) ; 
 int /*<<< orphan*/  zfs_prop_visible (int) ; 

__attribute__((used)) static void
zcp_dataset_system_props(dsl_dataset_t *ds, nvlist_t *nv)
{
	for (int prop = ZFS_PROP_TYPE; prop < ZFS_NUM_PROPS; prop++) {
		/* Do not display hidden props */
		if (!zfs_prop_visible(prop))
			continue;
		/* Do not display props not valid for this dataset */
		if (!prop_valid_for_ds(ds, prop))
			continue;
		fnvlist_add_boolean(nv, zfs_prop_to_name(prop));
	}
}