#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct swaybar {int /*<<< orphan*/  eventloop; int /*<<< orphan*/  display; scalar_t__ running; TYPE_2__* tray; TYPE_1__* status; int /*<<< orphan*/  ipc_event_socketfd; } ;
struct TYPE_4__ {struct swaybar* bus; int /*<<< orphan*/  fd; } ;
struct TYPE_3__ {int /*<<< orphan*/  read_fd; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  display_in ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  ipc_in ; 
 int /*<<< orphan*/  loop_add_fd (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct swaybar*) ; 
 int /*<<< orphan*/  loop_poll (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  status_in ; 
 int /*<<< orphan*/  tray_in ; 
 int wl_display_flush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_get_fd (int /*<<< orphan*/ ) ; 

void bar_run(struct swaybar *bar) {
	loop_add_fd(bar->eventloop, wl_display_get_fd(bar->display), POLLIN,
			display_in, bar);
	loop_add_fd(bar->eventloop, bar->ipc_event_socketfd, POLLIN, ipc_in, bar);
	if (bar->status) {
		loop_add_fd(bar->eventloop, bar->status->read_fd, POLLIN,
				status_in, bar);
	}
#if HAVE_TRAY
	if (bar->tray) {
		loop_add_fd(bar->eventloop, bar->tray->fd, POLLIN, tray_in, bar->tray->bus);
	}
#endif
	while (bar->running) {
		errno = 0;
		if (wl_display_flush(bar->display) == -1 && errno != EAGAIN) {
			break;
		}
		loop_poll(bar->eventloop);
	}
}