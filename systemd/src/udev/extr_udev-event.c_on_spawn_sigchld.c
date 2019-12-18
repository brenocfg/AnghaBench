#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int si_code; int si_status; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  sd_event_source ;
struct TYPE_6__ {int /*<<< orphan*/  cmd; int /*<<< orphan*/  device; int /*<<< orphan*/  accept_failure; } ;
typedef  TYPE_2__ Spawn ;

/* Variables and functions */
#define  CLD_DUMPED 130 
#define  CLD_EXITED 129 
#define  CLD_KILLED 128 
 int EIO ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_device_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_device_error (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  log_device_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_event_source_get_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_to_string (int) ; 

__attribute__((used)) static int on_spawn_sigchld(sd_event_source *s, const siginfo_t *si, void *userdata) {
        Spawn *spawn = userdata;
        int ret = -EIO;

        assert(spawn);

        switch (si->si_code) {
        case CLD_EXITED:
                if (si->si_status == 0)
                        log_device_debug(spawn->device, "Process '%s' succeeded.", spawn->cmd);
                else
                        log_device_full(spawn->device, spawn->accept_failure ? LOG_DEBUG : LOG_WARNING, 0,
                                        "Process '%s' failed with exit code %i.", spawn->cmd, si->si_status);
                ret = si->si_status;
                break;
        case CLD_KILLED:
        case CLD_DUMPED:
                log_device_error(spawn->device, "Process '%s' terminated by signal %s.", spawn->cmd, signal_to_string(si->si_status));
                break;
        default:
                log_device_error(spawn->device, "Process '%s' failed due to unknown reason.", spawn->cmd);
        }

        sd_event_exit(sd_event_source_get_event(s), ret);
        return 1;
}