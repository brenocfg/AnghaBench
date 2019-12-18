#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ si_code; scalar_t__ si_status; } ;
typedef  TYPE_1__ siginfo_t ;
struct TYPE_9__ {scalar_t__ pid; } ;
typedef  TYPE_2__ sd_event_source ;
typedef  TYPE_2__ Transfer ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_DUMPED ; 
 scalar_t__ CLD_EXITED ; 
 int /*<<< orphan*/  CLD_KILLED ; 
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*) ; 
 int /*<<< orphan*/  log_error (char*,...) ; 
 int /*<<< orphan*/  signal_to_string (scalar_t__) ; 
 int transfer_finalize (TYPE_2__*,int) ; 

__attribute__((used)) static int transfer_on_pid(sd_event_source *s, const siginfo_t *si, void *userdata) {
        Transfer *t = userdata;
        bool success = false;

        assert(s);
        assert(t);

        if (si->si_code == CLD_EXITED) {
                if (si->si_status != 0)
                        log_error("Transfer process failed with exit code %i.", si->si_status);
                else {
                        log_debug("Transfer process succeeded.");
                        success = true;
                }

        } else if (IN_SET(si->si_code, CLD_KILLED, CLD_DUMPED))
                log_error("Transfer process terminated by signal %s.", signal_to_string(si->si_status));
        else
                log_error("Transfer process failed due to unknown reason.");

        t->pid = 0;

        return transfer_finalize(t, success);
}