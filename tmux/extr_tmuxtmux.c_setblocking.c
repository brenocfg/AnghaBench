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
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

void
setblocking(int fd, int state)
{
	int mode;

	if ((mode = fcntl(fd, F_GETFL)) != -1) {
		if (!state)
			mode |= O_NONBLOCK;
		else
			mode &= ~O_NONBLOCK;
		fcntl(fd, F_SETFL, mode);
	}
}