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
struct flock {int l_start; int l_len; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  F_SETLK ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int /*<<< orphan*/  False ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  True ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 

BOOL
rd_lock_file(int fd, int start, int len)
{
	struct flock lock;

	lock.l_type = F_WRLCK;
	lock.l_whence = SEEK_SET;
	lock.l_start = start;
	lock.l_len = len;
	if (fcntl(fd, F_SETLK, &lock) == -1)
		return False;
	return True;
}