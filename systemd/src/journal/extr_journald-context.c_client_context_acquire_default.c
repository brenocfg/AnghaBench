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
struct ucred {int pid; int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; } ;
struct TYPE_5__ {int /*<<< orphan*/  pid1_context; int /*<<< orphan*/  my_context; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int client_context_acquire (TYPE_1__*,int,struct ucred*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getgid () ; 
 int getpid_cached () ; 
 int /*<<< orphan*/  getuid () ; 
 int /*<<< orphan*/  log_warning_errno (int,char*) ; 

void client_context_acquire_default(Server *s) {
        int r;

        assert(s);

        /* Ensure that our own and PID1's contexts are always pinned. Our own context is particularly useful to
         * generate driver messages. */

        if (!s->my_context) {
                struct ucred ucred = {
                        .pid = getpid_cached(),
                        .uid = getuid(),
                        .gid = getgid(),
                };

                r = client_context_acquire(s, ucred.pid, &ucred, NULL, 0, NULL, &s->my_context);
                if (r < 0)
                        log_warning_errno(r, "Failed to acquire our own context, ignoring: %m");
        }

        if (!s->pid1_context) {

                r = client_context_acquire(s, 1, NULL, NULL, 0, NULL, &s->pid1_context);
                if (r < 0)
                        log_warning_errno(r, "Failed to acquire PID1's context, ignoring: %m");

        }
}