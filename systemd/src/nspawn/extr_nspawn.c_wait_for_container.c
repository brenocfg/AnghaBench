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
struct TYPE_3__ {int si_code; int si_status; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  ContainerStatus ;

/* Variables and functions */
#define  CLD_DUMPED 130 
#define  CLD_EXITED 129 
#define  CLD_KILLED 128 
 int /*<<< orphan*/  CONTAINER_REBOOTED ; 
 int /*<<< orphan*/  CONTAINER_TERMINATED ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_INFO ; 
 int SIGHUP ; 
 int SIGINT ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  arg_machine ; 
 int /*<<< orphan*/  arg_quiet ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_full (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int log_warning_errno (int,char*) ; 
 int /*<<< orphan*/  signal_to_string (int) ; 
 int wait_for_terminate (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int wait_for_container(pid_t pid, ContainerStatus *container) {
        siginfo_t status;
        int r;

        r = wait_for_terminate(pid, &status);
        if (r < 0)
                return log_warning_errno(r, "Failed to wait for container: %m");

        switch (status.si_code) {

        case CLD_EXITED:
                if (status.si_status == 0)
                        log_full(arg_quiet ? LOG_DEBUG : LOG_INFO, "Container %s exited successfully.", arg_machine);
                else
                        log_full(arg_quiet ? LOG_DEBUG : LOG_INFO, "Container %s failed with error code %i.", arg_machine, status.si_status);

                *container = CONTAINER_TERMINATED;
                return status.si_status;

        case CLD_KILLED:
                if (status.si_status == SIGINT) {
                        log_full(arg_quiet ? LOG_DEBUG : LOG_INFO, "Container %s has been shut down.", arg_machine);
                        *container = CONTAINER_TERMINATED;
                        return 0;

                } else if (status.si_status == SIGHUP) {
                        log_full(arg_quiet ? LOG_DEBUG : LOG_INFO, "Container %s is being rebooted.", arg_machine);
                        *container = CONTAINER_REBOOTED;
                        return 0;
                }

                _fallthrough_;
        case CLD_DUMPED:
                return log_error_errno(SYNTHETIC_ERRNO(EIO),
                                       "Container %s terminated by signal %s.", arg_machine, signal_to_string(status.si_status));

        default:
                return log_error_errno(SYNTHETIC_ERRNO(EIO),
                                       "Container %s failed due to unknown reason.", arg_machine);
        }
}