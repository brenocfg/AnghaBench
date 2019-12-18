#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {char* cmd; char** vdev_names; int vdev_names_count; int cb_name_flags; int /*<<< orphan*/ * g_zfs; } ;
typedef  TYPE_1__ vdev_cmd_data_list_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  all_pools_for_each_vdev_gather_cb ; 
 int /*<<< orphan*/  all_pools_for_each_vdev_run_vcdl (TYPE_1__*) ; 
 int /*<<< orphan*/  for_each_pool (int,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_unique_cmd_columns (TYPE_1__*) ; 
 TYPE_1__* safe_malloc (int) ; 

vdev_cmd_data_list_t *
all_pools_for_each_vdev_run(int argc, char **argv, char *cmd,
    libzfs_handle_t *g_zfs, char **vdev_names, int vdev_names_count,
    int cb_name_flags)
{
	vdev_cmd_data_list_t *vcdl;
	vcdl = safe_malloc(sizeof (vdev_cmd_data_list_t));
	vcdl->cmd = cmd;

	vcdl->vdev_names = vdev_names;
	vcdl->vdev_names_count = vdev_names_count;
	vcdl->cb_name_flags = cb_name_flags;
	vcdl->g_zfs = g_zfs;

	/* Gather our list of all vdevs in all pools */
	for_each_pool(argc, argv, B_TRUE, NULL,
	    all_pools_for_each_vdev_gather_cb, vcdl);

	/* Run command on all vdevs in all pools */
	all_pools_for_each_vdev_run_vcdl(vcdl);

	/*
	 * vcdl->data[] now contains all the column names and values for each
	 * vdev.  We need to process that into a master list of unique column
	 * names, and figure out the width of each column.
	 */
	process_unique_cmd_columns(vcdl);

	return (vcdl);
}