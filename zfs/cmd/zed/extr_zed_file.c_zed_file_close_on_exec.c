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
 int /*<<< orphan*/  EBADF ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

int
zed_file_close_on_exec(int fd)
{
	int flags;

	if (fd < 0) {
		errno = EBADF;
		return (-1);
	}
	flags = fcntl(fd, F_GETFD);
	if (flags == -1)
		return (-1);

	flags |= FD_CLOEXEC;

	if (fcntl(fd, F_SETFD, flags) == -1)
		return (-1);

	return (0);
}