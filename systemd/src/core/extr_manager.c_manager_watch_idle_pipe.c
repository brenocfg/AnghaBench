#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* idle_pipe; scalar_t__ idle_pipe_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  manager_dispatch_idle_pipe_fd ; 
 int sd_event_add_io (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 

__attribute__((used)) static int manager_watch_idle_pipe(Manager *m) {
        int r;

        assert(m);

        if (m->idle_pipe_event_source)
                return 0;

        if (m->idle_pipe[2] < 0)
                return 0;

        r = sd_event_add_io(m->event, &m->idle_pipe_event_source, m->idle_pipe[2], EPOLLIN, manager_dispatch_idle_pipe_fd, m);
        if (r < 0)
                return log_error_errno(r, "Failed to watch idle pipe: %m");

        (void) sd_event_source_set_description(m->idle_pipe_event_source, "manager-idle-pipe");

        return 0;
}