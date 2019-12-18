#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_2__ zfs_handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_8__ {int zc_cookie; int zc_objset_type; int /*<<< orphan*/  zc_name; TYPE_1__ member_0; } ;
typedef  TYPE_3__ zfs_cmd_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_SEND_PROGRESS ; 
 int errno ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 

int
zfs_send_progress(zfs_handle_t *zhp, int fd, uint64_t *bytes_written,
    uint64_t *blocks_visited)
{
	zfs_cmd_t zc = { {0} };
	(void) strlcpy(zc.zc_name, zhp->zfs_name, sizeof (zc.zc_name));
	zc.zc_cookie = fd;
	if (zfs_ioctl(zhp->zfs_hdl, ZFS_IOC_SEND_PROGRESS, &zc) != 0)
		return (errno);
	if (bytes_written != NULL)
		*bytes_written = zc.zc_cookie;
	if (blocks_visited != NULL)
		*blocks_visited = zc.zc_objset_type;
	return (0);
}