#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {char* member_0; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_LOG_HISTORY ; 
 int /*<<< orphan*/  fnvlist_add_string (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/ * fnvlist_alloc () ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zcmd_free_nvlists (TYPE_1__*) ; 
 int zcmd_write_src_nvlist (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zfs_ioctl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

int
zpool_log_history(libzfs_handle_t *hdl, const char *message)
{
	zfs_cmd_t zc = {"\0"};
	nvlist_t *args;
	int err;

	args = fnvlist_alloc();
	fnvlist_add_string(args, "message", message);
	err = zcmd_write_src_nvlist(hdl, &zc, args);
	if (err == 0)
		err = zfs_ioctl(hdl, ZFS_IOC_LOG_HISTORY, &zc);
	nvlist_free(args);
	zcmd_free_nvlists(&zc);
	return (err);
}