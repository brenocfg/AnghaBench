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
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  errno ; 

int vlc_socketpair(int pf, int type, int proto, int fds[2], bool nonblock)
{
    (void) pf; (void) type; (void) proto; (void) fds; (void) nonblock;
    errno = ENOSYS;
    return -1;
}