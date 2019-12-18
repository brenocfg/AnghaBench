#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_4__ {int cb_iteration; int cb_flags; int /*<<< orphan*/ * vcdl; int /*<<< orphan*/  cb_vdev_names_count; scalar_t__ cb_verbose; int /*<<< orphan*/  cb_scripted; } ;
typedef  TYPE_1__ iostat_cbdata_t ;

/* Variables and functions */
 int IOS_ANYHISTO_M ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  print_cmd_columns (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  print_iostat_separator (TYPE_1__*) ; 
 int print_vdev_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zpool_get_name (int /*<<< orphan*/ *) ; 

int
print_iostat(zpool_handle_t *zhp, void *data)
{
	iostat_cbdata_t *cb = data;
	nvlist_t *oldconfig, *newconfig;
	nvlist_t *oldnvroot, *newnvroot;
	int ret;

	newconfig = zpool_get_config(zhp, &oldconfig);

	if (cb->cb_iteration == 1)
		oldconfig = NULL;

	verify(nvlist_lookup_nvlist(newconfig, ZPOOL_CONFIG_VDEV_TREE,
	    &newnvroot) == 0);

	if (oldconfig == NULL)
		oldnvroot = NULL;
	else
		verify(nvlist_lookup_nvlist(oldconfig, ZPOOL_CONFIG_VDEV_TREE,
		    &oldnvroot) == 0);

	ret = print_vdev_stats(zhp, zpool_get_name(zhp), oldnvroot, newnvroot,
	    cb, 0);
	if ((ret != 0) && !(cb->cb_flags & IOS_ANYHISTO_M) &&
	    !cb->cb_scripted && cb->cb_verbose && !cb->cb_vdev_names_count) {
		print_iostat_separator(cb);
		if (cb->vcdl != NULL) {
			print_cmd_columns(cb->vcdl, 1);
		}
		printf("\n");
	}

	return (ret);
}