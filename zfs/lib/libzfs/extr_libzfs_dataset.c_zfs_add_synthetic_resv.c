#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  zfs_prop_t ;
struct TYPE_6__ {int /*<<< orphan*/  zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_PROP_VOLBLOCKSIZE ; 
 int /*<<< orphan*/  ZFS_PROP_VOLSIZE ; 
 int /*<<< orphan*/  fnvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  fnvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  no_memory (int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ zfs_prop_get_int (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_to_name (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_which_resv_prop (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zpool_handle (TYPE_1__*) ; 
 scalar_t__ zvol_volsize_to_reservation (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 

int
zfs_add_synthetic_resv(zfs_handle_t *zhp, nvlist_t *nvl)
{
	uint64_t old_volsize;
	uint64_t new_volsize;
	uint64_t old_reservation;
	uint64_t new_reservation;
	zfs_prop_t resv_prop;
	nvlist_t *props;
	zpool_handle_t *zph = zpool_handle(zhp);

	/*
	 * If this is an existing volume, and someone is setting the volsize,
	 * make sure that it matches the reservation, or add it if necessary.
	 */
	old_volsize = zfs_prop_get_int(zhp, ZFS_PROP_VOLSIZE);
	if (zfs_which_resv_prop(zhp, &resv_prop) < 0)
		return (-1);
	old_reservation = zfs_prop_get_int(zhp, resv_prop);

	props = fnvlist_alloc();
	fnvlist_add_uint64(props, zfs_prop_to_name(ZFS_PROP_VOLBLOCKSIZE),
	    zfs_prop_get_int(zhp, ZFS_PROP_VOLBLOCKSIZE));

	if ((zvol_volsize_to_reservation(zph, old_volsize, props) !=
	    old_reservation) || nvlist_exists(nvl,
	    zfs_prop_to_name(resv_prop))) {
		fnvlist_free(props);
		return (0);
	}
	if (nvlist_lookup_uint64(nvl, zfs_prop_to_name(ZFS_PROP_VOLSIZE),
	    &new_volsize) != 0) {
		fnvlist_free(props);
		return (-1);
	}
	new_reservation = zvol_volsize_to_reservation(zph, new_volsize, props);
	fnvlist_free(props);

	if (nvlist_add_uint64(nvl, zfs_prop_to_name(resv_prop),
	    new_reservation) != 0) {
		(void) no_memory(zhp->zfs_hdl);
		return (-1);
	}
	return (1);
}