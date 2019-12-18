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
 int EINVAL ; 
 char* MNTTYPE_ZFS ; 
 int MS_DETACH ; 
 int MS_FORCE ; 
 int STDERR_VERBOSE ; 
 int STDOUT_VERBOSE ; 
 int libzfs_run_process (char*,char**,int) ; 

int
do_unmount(const char *mntpt, int flags)
{
	char force_opt[] = "-f";
	char lazy_opt[] = "-l";
	char *argv[7] = {
	    "/bin/umount",
	    "-t", MNTTYPE_ZFS,
	    NULL, NULL, NULL, NULL };
	int rc, count = 3;

	if (flags & MS_FORCE) {
		argv[count] = force_opt;
		count++;
	}

	if (flags & MS_DETACH) {
		argv[count] = lazy_opt;
		count++;
	}

	argv[count] = (char *)mntpt;
	rc = libzfs_run_process(argv[0], argv, STDOUT_VERBOSE|STDERR_VERBOSE);

	return (rc ? EINVAL : 0);
}