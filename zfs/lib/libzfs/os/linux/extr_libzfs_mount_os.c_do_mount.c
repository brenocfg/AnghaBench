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

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int ENXIO ; 
 int EPIPE ; 
 char* MNTTYPE_ZFS ; 
 int MOUNT_BUSY ; 
 int MOUNT_FILEIO ; 
 int MOUNT_SOFTWARE ; 
 int MOUNT_SYSERR ; 
 int MOUNT_USAGE ; 
 int MOUNT_USER ; 
 int STDERR_VERBOSE ; 
 int STDOUT_VERBOSE ; 
 int libzfs_run_process (char*,char**,int) ; 

int
do_mount(const char *src, const char *mntpt, char *opts, int flags)
{
	char *argv[9] = {
	    "/bin/mount",
	    "--no-canonicalize",
	    "-t", MNTTYPE_ZFS,
	    "-o", opts,
	    (char *)src,
	    (char *)mntpt,
	    (char *)NULL };
	int rc;

	/* Return only the most critical mount error */
	rc = libzfs_run_process(argv[0], argv, STDOUT_VERBOSE|STDERR_VERBOSE);
	if (rc) {
		if (rc & MOUNT_FILEIO)
			return (EIO);
		if (rc & MOUNT_USER)
			return (EINTR);
		if (rc & MOUNT_SOFTWARE)
			return (EPIPE);
		if (rc & MOUNT_BUSY)
			return (EBUSY);
		if (rc & MOUNT_SYSERR)
			return (EAGAIN);
		if (rc & MOUNT_USAGE)
			return (EINVAL);

		return (ENXIO); /* Generic error */
	}

	return (0);
}