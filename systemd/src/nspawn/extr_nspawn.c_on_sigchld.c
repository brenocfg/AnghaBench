#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct signalfd_siginfo {int dummy; } ;
struct TYPE_3__ {scalar_t__ si_pid; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  struct signalfd_siginfo const sd_event_source ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ PTR_TO_PID (void*) ; 
 int /*<<< orphan*/  P_ALL ; 
 int /*<<< orphan*/  P_PID ; 
 int WEXITED ; 
 int WNOHANG ; 
 int WNOWAIT ; 
 int /*<<< orphan*/  assert (struct signalfd_siginfo const*) ; 
 int /*<<< orphan*/  errno ; 
 int log_error_errno (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_get_event (struct signalfd_siginfo const*) ; 
 scalar_t__ waitid (int /*<<< orphan*/ ,scalar_t__,TYPE_1__*,int) ; 

__attribute__((used)) static int on_sigchld(sd_event_source *s, const struct signalfd_siginfo *ssi, void *userdata) {
        pid_t pid;

        assert(s);
        assert(ssi);

        pid = PTR_TO_PID(userdata);

        for (;;) {
                siginfo_t si = {};

                if (waitid(P_ALL, 0, &si, WNOHANG|WNOWAIT|WEXITED) < 0)
                        return log_error_errno(errno, "Failed to waitid(): %m");
                if (si.si_pid == 0) /* No pending children. */
                        break;
                if (si.si_pid == pid) {
                        /* The main process we care for has exited. Return from
                         * signal handler but leave the zombie. */
                        sd_event_exit(sd_event_source_get_event(s), 0);
                        break;
                }

                /* Reap all other children. */
                (void) waitid(P_PID, si.si_pid, &si, WNOHANG|WEXITED);
        }

        return 0;
}