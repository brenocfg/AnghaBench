#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ zc_ena; } ;
struct TYPE_8__ {int /*<<< orphan*/  zc_node; TYPE_1__ zc_data; } ;
typedef  TYPE_2__ zfs_case_t ;
typedef  int /*<<< orphan*/  uu_list_walk_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/  UU_WALK_ROBUST ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,unsigned long long) ; 
 int /*<<< orphan*/  fmd_hdl_free (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/ * fmd_hdl_getspecific (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libzfs_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_list_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_node_fini (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_pool_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_list_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  uu_list_walk_end (int /*<<< orphan*/ *) ; 
 TYPE_2__* uu_list_walk_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * uu_list_walk_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_case_pool ; 
 int /*<<< orphan*/  zfs_cases ; 

void
_zfs_diagnosis_fini(fmd_hdl_t *hdl)
{
	zfs_case_t *zcp;
	uu_list_walk_t *walk;
	libzfs_handle_t *zhdl;

	/*
	 * Remove all active cases.
	 */
	walk = uu_list_walk_start(zfs_cases, UU_WALK_ROBUST);
	while ((zcp = uu_list_walk_next(walk)) != NULL) {
		fmd_hdl_debug(hdl, "removing case ena %llu",
		    (long long unsigned)zcp->zc_data.zc_ena);
		uu_list_remove(zfs_cases, zcp);
		uu_list_node_fini(zcp, &zcp->zc_node, zfs_case_pool);
		fmd_hdl_free(hdl, zcp, sizeof (zfs_case_t));
	}
	uu_list_walk_end(walk);

	uu_list_destroy(zfs_cases);
	uu_list_pool_destroy(zfs_case_pool);

	zhdl = fmd_hdl_getspecific(hdl);
	libzfs_fini(zhdl);
}