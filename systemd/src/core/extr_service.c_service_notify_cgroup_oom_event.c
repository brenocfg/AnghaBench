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
struct TYPE_5__ {scalar_t__ oom_policy; int state; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 scalar_t__ OOM_CONTINUE ; 
 scalar_t__ OOM_KILL ; 
 scalar_t__ OOM_STOP ; 
 TYPE_1__* SERVICE (int /*<<< orphan*/ *) ; 
#define  SERVICE_CONDITION 140 
#define  SERVICE_EXITED 139 
 int /*<<< orphan*/  SERVICE_FAILURE_OOM_KILL ; 
#define  SERVICE_FINAL_SIGKILL 138 
#define  SERVICE_FINAL_SIGTERM 137 
#define  SERVICE_RUNNING 136 
#define  SERVICE_START 135 
#define  SERVICE_START_POST 134 
#define  SERVICE_START_PRE 133 
#define  SERVICE_STOP 132 
#define  SERVICE_STOP_POST 131 
#define  SERVICE_STOP_SIGKILL 130 
#define  SERVICE_STOP_SIGTERM 129 
#define  SERVICE_STOP_WATCHDOG 128 
 int /*<<< orphan*/  SERVICE_SUCCESS ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  service_enter_signal (TYPE_1__*,int const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_enter_stop (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_notify_cgroup_oom_event(Unit *u) {
        Service *s = SERVICE(u);

        log_unit_debug(u, "Process of control group was killed by the OOM killer.");

        if (s->oom_policy == OOM_CONTINUE)
                return;

        switch (s->state) {

        case SERVICE_CONDITION:
        case SERVICE_START_PRE:
        case SERVICE_START:
        case SERVICE_START_POST:
        case SERVICE_STOP:
                if (s->oom_policy == OOM_STOP)
                        service_enter_signal(s, SERVICE_STOP_SIGTERM, SERVICE_FAILURE_OOM_KILL);
                else if (s->oom_policy == OOM_KILL)
                        service_enter_signal(s, SERVICE_STOP_SIGKILL, SERVICE_FAILURE_OOM_KILL);

                break;

        case SERVICE_EXITED:
        case SERVICE_RUNNING:
                if (s->oom_policy == OOM_STOP)
                        service_enter_stop(s, SERVICE_FAILURE_OOM_KILL);
                else if (s->oom_policy == OOM_KILL)
                        service_enter_signal(s, SERVICE_STOP_SIGKILL, SERVICE_FAILURE_OOM_KILL);

                break;

        case SERVICE_STOP_WATCHDOG:
        case SERVICE_STOP_SIGTERM:
                service_enter_signal(s, SERVICE_STOP_SIGKILL, SERVICE_FAILURE_OOM_KILL);
                break;

        case SERVICE_STOP_SIGKILL:
        case SERVICE_FINAL_SIGKILL:
                if (s->result == SERVICE_SUCCESS)
                        s->result = SERVICE_FAILURE_OOM_KILL;
                break;

        case SERVICE_STOP_POST:
        case SERVICE_FINAL_SIGTERM:
                service_enter_signal(s, SERVICE_FINAL_SIGKILL, SERVICE_FAILURE_OOM_KILL);
                break;

        default:
                ;
        }
}