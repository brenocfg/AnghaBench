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
struct TYPE_5__ {scalar_t__ zc_pool_guid; scalar_t__ zc_vdev_guid; scalar_t__ zc_has_remove_timer; } ;
struct TYPE_6__ {TYPE_1__ zc_data; int /*<<< orphan*/  zc_remove_timer; int /*<<< orphan*/  zc_case; } ;
typedef  TYPE_2__ zfs_case_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME ; 
 int /*<<< orphan*/  FM_FMRI_SCHEME_ZFS ; 
 int /*<<< orphan*/  FM_FMRI_ZFS_POOL ; 
 int /*<<< orphan*/  FM_FMRI_ZFS_VDEV ; 
 int /*<<< orphan*/  FM_VERSION ; 
 int /*<<< orphan*/  ZFS_SCHEME_VERSION0 ; 
 int /*<<< orphan*/  fmd_case_add_suspect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_case_solve (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fmd_nvl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fmd_nvl_create_fault (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fmd_timer_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  nvlist_add_uint8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_case_serialize (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void
zfs_case_solve(fmd_hdl_t *hdl, zfs_case_t *zcp, const char *faultname,
    boolean_t checkunusable)
{
	nvlist_t *detector, *fault;
	boolean_t serialize;
	nvlist_t *fru = NULL;
	fmd_hdl_debug(hdl, "solving fault '%s'", faultname);

	/*
	 * Construct the detector from the case data.  The detector is in the
	 * ZFS scheme, and is either the pool or the vdev, depending on whether
	 * this is a vdev or pool fault.
	 */
	detector = fmd_nvl_alloc(hdl, FMD_SLEEP);

	(void) nvlist_add_uint8(detector, FM_VERSION, ZFS_SCHEME_VERSION0);
	(void) nvlist_add_string(detector, FM_FMRI_SCHEME, FM_FMRI_SCHEME_ZFS);
	(void) nvlist_add_uint64(detector, FM_FMRI_ZFS_POOL,
	    zcp->zc_data.zc_pool_guid);
	if (zcp->zc_data.zc_vdev_guid != 0) {
		(void) nvlist_add_uint64(detector, FM_FMRI_ZFS_VDEV,
		    zcp->zc_data.zc_vdev_guid);
	}

	fault = fmd_nvl_create_fault(hdl, faultname, 100, detector,
	    fru, detector);
	fmd_case_add_suspect(hdl, zcp->zc_case, fault);

	nvlist_free(fru);

	fmd_case_solve(hdl, zcp->zc_case);

	serialize = B_FALSE;
	if (zcp->zc_data.zc_has_remove_timer) {
		fmd_timer_remove(hdl, zcp->zc_remove_timer);
		zcp->zc_data.zc_has_remove_timer = 0;
		serialize = B_TRUE;
	}
	if (serialize)
		zfs_case_serialize(hdl, zcp);

	nvlist_free(detector);
}