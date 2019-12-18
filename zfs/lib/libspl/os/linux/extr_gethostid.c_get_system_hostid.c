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
 unsigned long HOSTID_MASK ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 unsigned long get_spl_hostid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int read (int,unsigned long*,int) ; 

unsigned long
get_system_hostid(void)
{
	unsigned long system_hostid = get_spl_hostid();
	/*
	 * We do not use the library call gethostid() because
	 * it generates a hostid value that the kernel is
	 * unaware of, if the spl_hostid module parameter has not
	 * been set and there is no system hostid file (e.g.
	 * /etc/hostid).  The kernel and userspace must agree.
	 * See comments above hostid_read() in the SPL.
	 */
	if (system_hostid == 0) {
		int fd, rc;
		unsigned long hostid;
		int hostid_size = 4;  /* 4 bytes regardless of arch */

		fd = open("/etc/hostid", O_RDONLY);
		if (fd >= 0) {
			rc = read(fd, &hostid, hostid_size);
			if (rc > 0)
				system_hostid = (hostid & HOSTID_MASK);
			close(fd);
		}
	}
	return (system_hostid);
}