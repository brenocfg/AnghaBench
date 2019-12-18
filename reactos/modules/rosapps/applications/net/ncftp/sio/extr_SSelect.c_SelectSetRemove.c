#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  numfds; int /*<<< orphan*/  fds; } ;
typedef  TYPE_1__* SelectSetPtr ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (int const,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_ISSET (int const,int /*<<< orphan*/ *) ; 

void
SelectSetRemove(SelectSetPtr const ssp, const int fd)
{
	if ((fd >= 0) && (FD_ISSET(fd, &ssp->fds))) {
		FD_CLR(fd, &ssp->fds);
		/* Note that maxfd is left alone, even if maxfd was
		 * this one.  That is okay.
		 */
		--ssp->numfds;
	}
}