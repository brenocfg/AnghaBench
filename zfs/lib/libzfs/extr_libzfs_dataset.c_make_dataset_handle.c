#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  zfs_name; int /*<<< orphan*/ * zfs_hdl; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct TYPE_13__ {char* member_0; } ;
typedef  TYPE_2__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int get_stats_ioctl (TYPE_1__*,TYPE_2__*) ; 
 int make_dataset_handle_common (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ zcmd_alloc_dst_nvlist (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_2__*) ; 

zfs_handle_t *
make_dataset_handle(libzfs_handle_t *hdl, const char *path)
{
	zfs_cmd_t zc = {"\0"};

	zfs_handle_t *zhp = calloc(1, sizeof (zfs_handle_t));

	if (zhp == NULL)
		return (NULL);

	zhp->zfs_hdl = hdl;
	(void) strlcpy(zhp->zfs_name, path, sizeof (zhp->zfs_name));
	if (zcmd_alloc_dst_nvlist(hdl, &zc, 0) != 0) {
		free(zhp);
		return (NULL);
	}
	if (get_stats_ioctl(zhp, &zc) == -1) {
		zcmd_free_nvlists(&zc);
		free(zhp);
		return (NULL);
	}
	if (make_dataset_handle_common(zhp, &zc) == -1) {
		free(zhp);
		zhp = NULL;
	}
	zcmd_free_nvlists(&zc);
	return (zhp);
}