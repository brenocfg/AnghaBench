#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* member_0; char* zc_name; } ;
typedef  TYPE_1__ zfs_cmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZFS_IOC_DESTROY ; 
 int errno ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  zfs_fd ; 

__attribute__((used)) static int
zfs_destroy(const char *dataset)
{
	zfs_cmd_t zc = {"\0"};
	int err;

	(void) strlcpy(zc.zc_name, dataset, sizeof (zc.zc_name));
	zc.zc_name[sizeof (zc.zc_name) - 1] = '\0';
	err = ioctl(zfs_fd, ZFS_IOC_DESTROY, &zc);

	return (err == 0 ? 0 : errno);
}