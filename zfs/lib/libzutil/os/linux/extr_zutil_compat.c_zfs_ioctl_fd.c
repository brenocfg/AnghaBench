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
typedef  int /*<<< orphan*/  zfs_cmd_t ;

/* Variables and functions */
 int ioctl (int,unsigned long,int /*<<< orphan*/ *) ; 

int
zfs_ioctl_fd(int fd, unsigned long request, zfs_cmd_t *zc)
{
	return (ioctl(fd, request, zc));
}