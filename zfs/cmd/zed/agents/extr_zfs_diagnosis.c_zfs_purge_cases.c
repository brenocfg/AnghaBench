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
struct TYPE_6__ {int /*<<< orphan*/  zc_case; int /*<<< orphan*/  zc_present; } ;
typedef  TYPE_1__ zfs_case_t ;
typedef  int /*<<< orphan*/  uu_list_walk_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int /*<<< orphan*/  fmd_case_close (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_1__* uu_list_next (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  uu_list_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_1__* uu_list_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_list_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_cases ; 
 int /*<<< orphan*/  zfs_mark_pool ; 
 scalar_t__ zpool_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
zfs_purge_cases(fmd_hdl_t *hdl)
{
	zfs_case_t *zcp;
	uu_list_walk_t *walk;
	libzfs_handle_t *zhdl = fmd_hdl_getspecific(hdl);

	/*
	 * There is no way to open a pool by GUID, or lookup a vdev by GUID.  No
	 * matter what we do, we're going to have to stomach an O(vdevs * cases)
	 * algorithm.  In reality, both quantities are likely so small that
	 * neither will matter. Given that iterating over pools is more
	 * expensive than iterating over the in-memory case list, we opt for a
	 * 'present' flag in each case that starts off cleared.  We then iterate
	 * over all pools, marking those that are still present, and removing
	 * those that aren't found.
	 *
	 * Note that we could also construct an FMRI and rely on
	 * fmd_nvl_fmri_present(), but this would end up doing the same search.
	 */

	/*
	 * Mark the cases as not present.
	 */
	for (zcp = uu_list_first(zfs_cases); zcp != NULL;
	    zcp = uu_list_next(zfs_cases, zcp))
		zcp->zc_present = B_FALSE;

	/*
	 * Iterate over all pools and mark the pools and vdevs found.  If this
	 * fails (most probably because we're out of memory), then don't close
	 * any of the cases and we cannot be sure they are accurate.
	 */
	if (zpool_iter(zhdl, zfs_mark_pool, NULL) != 0)
		return;

	/*
	 * Remove those cases which were not found.
	 */
	walk = uu_list_walk_start(zfs_cases, UU_WALK_ROBUST);
	while ((zcp = uu_list_walk_next(walk)) != NULL) {
		if (!zcp->zc_present)
			fmd_case_close(hdl, zcp->zc_case);
	}
	uu_list_walk_end(walk);
}