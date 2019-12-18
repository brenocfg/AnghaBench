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
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_PROP_CLONES ; 
 int /*<<< orphan*/  ZPROP_VALUE ; 
 int /*<<< orphan*/  fnvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 scalar_t__ get_clones_stat_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 

void
get_clones_stat(dsl_dataset_t *ds, nvlist_t *nv)
{
	nvlist_t *propval = fnvlist_alloc();
	nvlist_t *val;

	/*
	 * We use nvlist_alloc() instead of fnvlist_alloc() because the
	 * latter would allocate the list with NV_UNIQUE_NAME flag.
	 * As a result, every time a clone name is appended to the list
	 * it would be (linearly) searched for a duplicate name.
	 * We already know that all clone names must be unique and we
	 * want avoid the quadratic complexity of double-checking that
	 * because we can have a large number of clones.
	 */
	VERIFY0(nvlist_alloc(&val, 0, KM_SLEEP));

	if (get_clones_stat_impl(ds, val) == 0) {
		fnvlist_add_nvlist(propval, ZPROP_VALUE, val);
		fnvlist_add_nvlist(nv, zfs_prop_to_name(ZFS_PROP_CLONES),
		    propval);
	}

	nvlist_free(val);
	nvlist_free(propval);
}