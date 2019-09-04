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
struct status_line {int read_fd; int write_fd; TYPE_1__* bar; } ;
struct TYPE_2__ {int /*<<< orphan*/  eventloop; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  loop_remove_fd (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void status_line_close_fds(struct status_line *status) {
	if (status->read_fd != -1) {
		loop_remove_fd(status->bar->eventloop, status->read_fd);
		close(status->read_fd);
		status->read_fd = -1;
	}
	if (status->write_fd != -1) {
		close(status->write_fd);
		status->write_fd = -1;
	}
}