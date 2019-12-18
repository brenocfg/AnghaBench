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
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLKFLSBUF ; 
 int /*<<< orphan*/  EZFS_NOCAP ; 
 int /*<<< orphan*/  EZFS_OPENFAILED ; 
 int O_DIRECT ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int VT_ENOSPC ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int efi_use_whole_disk (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fsync (int) ; 
 int /*<<< orphan*/  ioctl (int,int /*<<< orphan*/ ) ; 
 int open (char const*,int) ; 
 int zfs_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  zfs_error_aux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,...) ; 

int
zpool_relabel_disk(libzfs_handle_t *hdl, const char *path, const char *msg)
{
	int fd, error;

	if ((fd = open(path, O_RDWR|O_DIRECT)) < 0) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "relabel '%s': unable to open device: %d"), path, errno);
		return (zfs_error(hdl, EZFS_OPENFAILED, msg));
	}

	/*
	 * It's possible that we might encounter an error if the device
	 * does not have any unallocated space left. If so, we simply
	 * ignore that error and continue on.
	 *
	 * Also, we don't call efi_rescan() - that would just return EBUSY.
	 * The module will do it for us in vdev_disk_open().
	 */
	error = efi_use_whole_disk(fd);

	/* Flush the buffers to disk and invalidate the page cache. */
	(void) fsync(fd);
	(void) ioctl(fd, BLKFLSBUF);

	(void) close(fd);
	if (error && error != VT_ENOSPC) {
		zfs_error_aux(hdl, dgettext(TEXT_DOMAIN, "cannot "
		    "relabel '%s': unable to read disk capacity"), path);
		return (zfs_error(hdl, EZFS_NOCAP, msg));
	}
	return (0);
}