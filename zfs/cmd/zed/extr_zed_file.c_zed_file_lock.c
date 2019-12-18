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
struct flock {scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 

int
zed_file_lock(int fd)
{
	struct flock lock;

	if (fd < 0) {
		errno = EBADF;
		return (-1);
	}
	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = 0;
	lock.l_len = 0;

	if (fcntl(fd, F_SETLK, &lock) < 0) {
		if ((errno == EACCES) || (errno == EAGAIN))
			return (1);

		return (-1);
	}
	return (0);
}