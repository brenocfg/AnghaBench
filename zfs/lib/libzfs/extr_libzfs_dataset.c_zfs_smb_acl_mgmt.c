#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int zfs_smb_acl_op_t ;
struct TYPE_8__ {char* member_0; int /*<<< orphan*/  zc_string; scalar_t__ zc_cookie; int /*<<< orphan*/  zc_value; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
struct TYPE_9__ {int /*<<< orphan*/  libzfs_fd; } ;
typedef  TYPE_2__ libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZFS_IOC_SMB_ACL ; 
#define  ZFS_SMB_ACL_ADD 131 
#define  ZFS_SMB_ACL_PURGE 130 
#define  ZFS_SMB_ACL_REMOVE 129 
#define  ZFS_SMB_ACL_RENAME 128 
 int /*<<< orphan*/  ZFS_SMB_ACL_SRC ; 
 int /*<<< orphan*/  ZFS_SMB_ACL_TARGET ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  no_memory (TYPE_2__*) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  zcmd_write_src_nvlist (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_smb_acl_mgmt(libzfs_handle_t *hdl, char *dataset, char *path,
    zfs_smb_acl_op_t cmd, char *resource1, char *resource2)
{
	zfs_cmd_t zc = {"\0"};
	nvlist_t *nvlist = NULL;
	int error;

	(void) strlcpy(zc.zc_name, dataset, sizeof (zc.zc_name));
	(void) strlcpy(zc.zc_value, path, sizeof (zc.zc_value));
	zc.zc_cookie = (uint64_t)cmd;

	if (cmd == ZFS_SMB_ACL_RENAME) {
		if (nvlist_alloc(&nvlist, NV_UNIQUE_NAME, 0) != 0) {
			(void) no_memory(hdl);
			return (0);
		}
	}

	switch (cmd) {
	case ZFS_SMB_ACL_ADD:
	case ZFS_SMB_ACL_REMOVE:
		(void) strlcpy(zc.zc_string, resource1, sizeof (zc.zc_string));
		break;
	case ZFS_SMB_ACL_RENAME:
		if (nvlist_add_string(nvlist, ZFS_SMB_ACL_SRC,
		    resource1) != 0) {
				(void) no_memory(hdl);
				return (-1);
		}
		if (nvlist_add_string(nvlist, ZFS_SMB_ACL_TARGET,
		    resource2) != 0) {
				(void) no_memory(hdl);
				return (-1);
		}
		if (zcmd_write_src_nvlist(hdl, &zc, nvlist) != 0) {
			nvlist_free(nvlist);
			return (-1);
		}
		break;
	case ZFS_SMB_ACL_PURGE:
		break;
	default:
		return (-1);
	}
	error = ioctl(hdl->libzfs_fd, ZFS_IOC_SMB_ACL, &zc);
	nvlist_free(nvlist);
	return (error);
}