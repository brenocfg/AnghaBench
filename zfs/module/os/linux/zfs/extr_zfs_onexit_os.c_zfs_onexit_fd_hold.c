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
typedef  int /*<<< orphan*/  zfs_onexit_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZST_ONEXIT ; 
 int /*<<< orphan*/  zfs_onexit_fd_rele (int) ; 
 int /*<<< orphan*/ * zfsdev_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int zfsdev_getminor (int,int /*<<< orphan*/ *) ; 

int
zfs_onexit_fd_hold(int fd, minor_t *minorp)
{
	zfs_onexit_t *zo = NULL;
	int error;

	error = zfsdev_getminor(fd, minorp);
	if (error) {
		zfs_onexit_fd_rele(fd);
		return (error);
	}

	zo = zfsdev_get_state(*minorp, ZST_ONEXIT);
	if (zo == NULL) {
		zfs_onexit_fd_rele(fd);
		return (SET_ERROR(EBADF));
	}
	return (0);
}