#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int ServiceState ;
typedef  int /*<<< orphan*/  Service ;

/* Variables and functions */
 int /*<<< orphan*/  JOB_RESTART ; 
 int KILL_KILL ; 
 int KILL_RESTART ; 
 int KILL_TERMINATE ; 
 int KILL_WATCHDOG ; 
#define  SERVICE_FINAL_SIGKILL 132 
#define  SERVICE_FINAL_SIGTERM 131 
#define  SERVICE_STOP_SIGKILL 130 
#define  SERVICE_STOP_SIGTERM 129 
#define  SERVICE_STOP_WATCHDOG 128 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 int _KILL_OPERATION_INVALID ; 
 int /*<<< orphan*/  _fallthrough_ ; 
 int /*<<< orphan*/  unit_has_job_type (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int state_to_kill_operation(Service *s, ServiceState state) {
        switch (state) {

        case SERVICE_STOP_WATCHDOG:
                return KILL_WATCHDOG;

        case SERVICE_STOP_SIGTERM:
                if (unit_has_job_type(UNIT(s), JOB_RESTART))
                        return KILL_RESTART;
                _fallthrough_;

        case SERVICE_FINAL_SIGTERM:
                return KILL_TERMINATE;

        case SERVICE_STOP_SIGKILL:
        case SERVICE_FINAL_SIGKILL:
                return KILL_KILL;

        default:
                return _KILL_OPERATION_INVALID;
        }
}