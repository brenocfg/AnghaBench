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
typedef  scalar_t__ hrtime_t ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int ENOEXEC ; 
 int ENXIO ; 
 long MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long MILLISEC ; 
 int /*<<< orphan*/  MIN (long,int) ; 
 long NSEC2MSEC (scalar_t__) ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  ZFS_DEV ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 char* getenv (char*) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  libzfs_module_loaded (char const*) ; 
 scalar_t__ libzfs_run_process (char*,char**,int /*<<< orphan*/ ) ; 
 int open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncasecmp (char*,char*,int /*<<< orphan*/ ) ; 
 long strtol (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static int
libzfs_load_module_impl(const char *module)
{
	char *argv[4] = {"/sbin/modprobe", "-q", (char *)module, (char *)0};
	char *load_str, *timeout_str;
	long timeout = 10; /* seconds */
	long busy_timeout = 10; /* milliseconds */
	int load = 0, fd;
	hrtime_t start;

	/* Optionally request module loading */
	if (!libzfs_module_loaded(module)) {
		load_str = getenv("ZFS_MODULE_LOADING");
		if (load_str) {
			if (!strncasecmp(load_str, "YES", strlen("YES")) ||
			    !strncasecmp(load_str, "ON", strlen("ON")))
				load = 1;
			else
				load = 0;
		}

		if (load) {
			if (libzfs_run_process("/sbin/modprobe", argv, 0))
				return (ENOEXEC);
		}

		if (!libzfs_module_loaded(module))
			return (ENXIO);
	}

	/*
	 * Device creation by udev is asynchronous and waiting may be
	 * required.  Busy wait for 10ms and then fall back to polling every
	 * 10ms for the allowed timeout (default 10s, max 10m).  This is
	 * done to optimize for the common case where the device is
	 * immediately available and to avoid penalizing the possible
	 * case where udev is slow or unable to create the device.
	 */
	timeout_str = getenv("ZFS_MODULE_TIMEOUT");
	if (timeout_str) {
		timeout = strtol(timeout_str, NULL, 0);
		timeout = MAX(MIN(timeout, (10 * 60)), 0); /* 0 <= N <= 600 */
	}

	start = gethrtime();
	do {
		fd = open(ZFS_DEV, O_RDWR);
		if (fd >= 0) {
			(void) close(fd);
			return (0);
		} else if (errno != ENOENT) {
			return (errno);
		} else if (NSEC2MSEC(gethrtime() - start) < busy_timeout) {
			sched_yield();
		} else {
			usleep(10 * MILLISEC);
		}
	} while (NSEC2MSEC(gethrtime() - start) < (timeout * MILLISEC));

	return (ENOENT);
}