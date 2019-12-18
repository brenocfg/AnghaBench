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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  scalar_t__ uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VDEV_NAME_PATH ; 
 int /*<<< orphan*/  VDEV_TYPE_INDIRECT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  fnvlist_add_boolean (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/  nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,scalar_t__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
zpool_collect_leaves(zpool_handle_t *zhp, nvlist_t *nvroot, nvlist_t *res)
{
	uint_t children = 0;
	nvlist_t **child;
	uint_t i;

	(void) nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN,
	    &child, &children);

	if (children == 0) {
		char *path = zpool_vdev_name(g_zfs, zhp, nvroot,
		    VDEV_NAME_PATH);

		if (strcmp(path, VDEV_TYPE_INDIRECT) != 0)
			fnvlist_add_boolean(res, path);

		free(path);
		return;
	}

	for (i = 0; i < children; i++) {
		zpool_collect_leaves(zhp, child[i], res);
	}
}