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
typedef  size_t zfs_prop_t ;
struct TYPE_3__ {scalar_t__* zfs_props_table; int /*<<< orphan*/  zfs_props; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint8_t ;
typedef  int /*<<< orphan*/  nvpair_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 size_t ZPROP_INVAL ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_type (int /*<<< orphan*/ *) ; 
 size_t zfs_name_to_prop (int /*<<< orphan*/ ) ; 

void
zfs_prune_proplist(zfs_handle_t *zhp, uint8_t *props)
{
	nvpair_t *curr;
	nvpair_t *next;

	/*
	 * Keep a reference to the props-table against which we prune the
	 * properties.
	 */
	zhp->zfs_props_table = props;

	curr = nvlist_next_nvpair(zhp->zfs_props, NULL);

	while (curr) {
		zfs_prop_t zfs_prop = zfs_name_to_prop(nvpair_name(curr));
		next = nvlist_next_nvpair(zhp->zfs_props, curr);

		/*
		 * User properties will result in ZPROP_INVAL, and since we
		 * only know how to prune standard ZFS properties, we always
		 * leave these in the list.  This can also happen if we
		 * encounter an unknown DSL property (when running older
		 * software, for example).
		 */
		if (zfs_prop != ZPROP_INVAL && props[zfs_prop] == B_FALSE)
			(void) nvlist_remove(zhp->zfs_props,
			    nvpair_name(curr), nvpair_type(curr));
		curr = next;
	}
}