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
struct pollfd {int dummy; } ;
struct loop {int fd_capacity; void* timers; void* fd_events; int /*<<< orphan*/  fds; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct loop* calloc (int,int) ; 
 void* create_list () ; 
 int /*<<< orphan*/  malloc (int) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 

struct loop *loop_create(void) {
	struct loop *loop = calloc(1, sizeof(struct loop));
	if (!loop) {
		sway_log(SWAY_ERROR, "Unable to allocate memory for loop");
		return NULL;
	}
	loop->fd_capacity = 10;
	loop->fds = malloc(sizeof(struct pollfd) * loop->fd_capacity);
	loop->fd_events = create_list();
	loop->timers = create_list();
	return loop;
}