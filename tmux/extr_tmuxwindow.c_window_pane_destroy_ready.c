#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct window_pane {int pipe_fd; int flags; int /*<<< orphan*/  fd; TYPE_1__* pipe_event; } ;
struct TYPE_2__ {int /*<<< orphan*/  output; } ;

/* Variables and functions */
 scalar_t__ EVBUFFER_LENGTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIONREAD ; 
 int PANE_EXITED ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

int
window_pane_destroy_ready(struct window_pane *wp)
{
	int	n;

	if (wp->pipe_fd != -1) {
		if (EVBUFFER_LENGTH(wp->pipe_event->output) != 0)
			return (0);
		if (ioctl(wp->fd, FIONREAD, &n) != -1 && n > 0)
			return (0);
	}

	if (~wp->flags & PANE_EXITED)
		return (0);
	return (1);
}