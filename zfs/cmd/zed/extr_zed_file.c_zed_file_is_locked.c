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
struct flock {scalar_t__ l_type; int l_pid; scalar_t__ l_len; scalar_t__ l_start; int /*<<< orphan*/  l_whence; } ;
typedef  int pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  F_GETLK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 

pid_t
zed_file_is_locked(int fd)
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

	if (fcntl(fd, F_GETLK, &lock) < 0)
		return (-1);

	if (lock.l_type == F_UNLCK)
		return (0);

	return (lock.l_pid);
}