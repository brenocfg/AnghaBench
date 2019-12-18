#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  send_sigkill; int /*<<< orphan*/  kill_mode; } ;
struct TYPE_7__ {TYPE_1__ kill_context; } ;
typedef  TYPE_2__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KILL_CONTROL_GROUP ; 
 int /*<<< orphan*/  KILL_MIXED ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int log_unit_error_errno (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ unit_warn_leftover_processes (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int service_adverse_to_leftover_processes(Service *s) {
        assert(s);

        /* KillMode=mixed and control group are used to indicate that all process should be killed off.
         * SendSIGKILL is used for services that require a clean shutdown. These are typically database
         * service where a SigKilled process would result in a lengthy recovery and who's shutdown or
         * startup time is quite variable (so Timeout settings aren't of use).
         *
         * Here we take these two factors and refuse to start a service if there are existing processes
         * within a control group. Databases, while generally having some protection against multiple
         * instances running, lets not stress the rigor of these. Also ExecStartPre parts of the service
         * aren't as rigoriously written to protect aganst against multiple use. */
        if (unit_warn_leftover_processes(UNIT(s)) &&
            IN_SET(s->kill_context.kill_mode, KILL_MIXED, KILL_CONTROL_GROUP) &&
            !s->kill_context.send_sigkill)
               return log_unit_error_errno(UNIT(s), SYNTHETIC_ERRNO(EBUSY),
                                           "Will not start SendSIGKILL=no service of type KillMode=control-group or mixed while processes exist");

        return 0;
}