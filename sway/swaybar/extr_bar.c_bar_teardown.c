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
struct swaybar {int /*<<< orphan*/  mode; int /*<<< orphan*/  id; scalar_t__ status; int /*<<< orphan*/  ipc_socketfd; int /*<<< orphan*/  ipc_event_socketfd; scalar_t__ config; int /*<<< orphan*/  seats; int /*<<< orphan*/  unused_outputs; int /*<<< orphan*/  outputs; int /*<<< orphan*/  tray; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  destroy_tray (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_config (scalar_t__) ; 
 int /*<<< orphan*/  free_outputs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_seats (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  status_line_free (scalar_t__) ; 

void bar_teardown(struct swaybar *bar) {
#if HAVE_TRAY
	destroy_tray(bar->tray);
#endif
	free_outputs(&bar->outputs);
	free_outputs(&bar->unused_outputs);
	free_seats(&bar->seats);
	if (bar->config) {
		free_config(bar->config);
	}
	close(bar->ipc_event_socketfd);
	close(bar->ipc_socketfd);
	if (bar->status) {
		status_line_free(bar->status);
	}
	free(bar->id);
	free(bar->mode);
}