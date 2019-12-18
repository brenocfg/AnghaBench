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
struct TYPE_5__ {int /*<<< orphan*/  zi_guid; } ;
typedef  TYPE_1__ zinject_record_t ;
struct TYPE_6__ {char* member_0; int zc_cookie; int /*<<< orphan*/  zc_guid; int /*<<< orphan*/  zc_name; } ;
typedef  TYPE_2__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int VDEV_STATE_DEGRADED ; 
 int VDEV_STATE_FAULTED ; 
 int /*<<< orphan*/  ZFS_IOC_VDEV_SET_STATE ; 
 int /*<<< orphan*/  g_zfs ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 
 scalar_t__ zfs_ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int
perform_action(const char *pool, zinject_record_t *record, int cmd)
{
	zfs_cmd_t zc = {"\0"};

	ASSERT(cmd == VDEV_STATE_DEGRADED || cmd == VDEV_STATE_FAULTED);
	(void) strlcpy(zc.zc_name, pool, sizeof (zc.zc_name));
	zc.zc_guid = record->zi_guid;
	zc.zc_cookie = cmd;

	if (zfs_ioctl(g_zfs, ZFS_IOC_VDEV_SET_STATE, &zc) == 0)
		return (0);

	return (1);
}