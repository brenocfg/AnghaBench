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
 int /*<<< orphan*/  ERROR (char*,int,...) ; 
 int /*<<< orphan*/  O_WRONLY ; 
 int close (int) ; 
 int errno ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

__attribute__((used)) static int
drop_caches(void)
{
	char file[] = "/proc/sys/vm/drop_caches";
	int fd, rc;

	fd = open(file, O_WRONLY);
	if (fd == -1) {
		ERROR("Error %d: open(\"%s\", O_WRONLY)\n", errno, file);
		return (errno);
	}

	rc = write(fd, "3", 1);
	if ((rc == -1) || (rc != 1)) {
		ERROR("Error %d: write(%d, \"3\", 1)\n", errno, fd);
		(void) close(fd);
		return (errno);
	}

	rc = close(fd);
	if (rc == -1) {
		ERROR("Error %d: close(%d)\n", errno, fd);
		return (errno);
	}

	return (0);
}