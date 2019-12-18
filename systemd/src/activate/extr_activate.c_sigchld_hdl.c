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
struct TYPE_3__ {scalar_t__ si_pid; int /*<<< orphan*/  si_status; } ;
typedef  TYPE_1__ siginfo_t ;

/* Variables and functions */
 scalar_t__ ECHILD ; 
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 int /*<<< orphan*/  P_ALL ; 
 int WEXITED ; 
 int WNOHANG ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_error_errno (scalar_t__,char*) ; 
 int /*<<< orphan*/  log_info (char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int waitid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static void sigchld_hdl(int sig) {
        PROTECT_ERRNO;

        for (;;) {
                siginfo_t si;
                int r;

                si.si_pid = 0;
                r = waitid(P_ALL, 0, &si, WEXITED | WNOHANG);
                if (r < 0) {
                        if (errno != ECHILD)
                                log_error_errno(errno, "Failed to reap children: %m");
                        return;
                }
                if (si.si_pid == 0)
                        return;

                log_info("Child %d died with code %d", si.si_pid, si.si_status);
        }
}