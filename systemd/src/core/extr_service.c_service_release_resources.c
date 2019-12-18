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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ stdin_fd; scalar_t__ stdout_fd; scalar_t__ stderr_fd; int /*<<< orphan*/  fd_store; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*) ; 
 void* safe_close (scalar_t__) ; 
 int /*<<< orphan*/  service_release_fd_store (TYPE_1__*) ; 

__attribute__((used)) static void service_release_resources(Unit *u) {
        Service *s = SERVICE(u);

        assert(s);

        if (!s->fd_store && s->stdin_fd < 0 && s->stdout_fd < 0 && s->stderr_fd < 0)
                return;

        log_unit_debug(u, "Releasing resources.");

        s->stdin_fd = safe_close(s->stdin_fd);
        s->stdout_fd = safe_close(s->stdout_fd);
        s->stderr_fd = safe_close(s->stderr_fd);

        service_release_fd_store(s);
}