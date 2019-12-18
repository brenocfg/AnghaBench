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
struct swaybar {int /*<<< orphan*/  status; int /*<<< orphan*/  eventloop; } ;

/* Variables and functions */
 short POLLERR ; 
 short POLLHUP ; 
 int /*<<< orphan*/  loop_remove_fd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bar_dirty (struct swaybar*) ; 
 int /*<<< orphan*/  status_error (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ status_handle_readable (int /*<<< orphan*/ ) ; 

void status_in(int fd, short mask, void *data) {
	struct swaybar *bar = data;
	if (mask & (POLLHUP | POLLERR)) {
		status_error(bar->status, "[error reading from status command]");
		set_bar_dirty(bar);
		loop_remove_fd(bar->eventloop, fd);
	} else if (status_handle_readable(bar->status)) {
		set_bar_dirty(bar);
	}
}