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
struct loop {struct loop* fds; int /*<<< orphan*/  timers; int /*<<< orphan*/  fd_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct loop*) ; 
 int /*<<< orphan*/  list_free_items_and_destroy (int /*<<< orphan*/ ) ; 

void loop_destroy(struct loop *loop) {
	list_free_items_and_destroy(loop->fd_events);
	list_free_items_and_destroy(loop->timers);
	free(loop->fds);
	free(loop);
}