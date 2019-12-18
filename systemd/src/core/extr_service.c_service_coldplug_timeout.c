#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_13__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_11__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_14__ {int /*<<< orphan*/  monotonic; } ;
struct TYPE_16__ {TYPE_3__ state_change_timestamp; TYPE_1__ inactive_enter_timestamp; TYPE_4__ active_enter_timestamp; } ;
struct TYPE_12__ {int /*<<< orphan*/  timeout_clean_usec; } ;
struct TYPE_15__ {int deserialized_state; TYPE_2__ exec_context; int /*<<< orphan*/  restart_usec; int /*<<< orphan*/  timeout_stop_usec; int /*<<< orphan*/  runtime_max_usec; int /*<<< orphan*/  timeout_start_usec; } ;
typedef  TYPE_5__ Service ;

/* Variables and functions */
#define  SERVICE_AUTO_RESTART 142 
#define  SERVICE_CLEANING 141 
#define  SERVICE_CONDITION 140 
#define  SERVICE_FINAL_SIGKILL 139 
#define  SERVICE_FINAL_SIGTERM 138 
#define  SERVICE_RELOAD 137 
#define  SERVICE_RUNNING 136 
#define  SERVICE_START 135 
#define  SERVICE_START_POST 134 
#define  SERVICE_START_PRE 133 
#define  SERVICE_STOP 132 
#define  SERVICE_STOP_POST 131 
#define  SERVICE_STOP_SIGKILL 130 
#define  SERVICE_STOP_SIGTERM 129 
#define  SERVICE_STOP_WATCHDOG 128 
 TYPE_9__* UNIT (TYPE_5__*) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_5__*) ; 
 int /*<<< orphan*/  service_timeout_abort_usec (TYPE_5__*) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static usec_t service_coldplug_timeout(Service *s) {
        assert(s);

        switch (s->deserialized_state) {

        case SERVICE_CONDITION:
        case SERVICE_START_PRE:
        case SERVICE_START:
        case SERVICE_START_POST:
        case SERVICE_RELOAD:
                return usec_add(UNIT(s)->state_change_timestamp.monotonic, s->timeout_start_usec);

        case SERVICE_RUNNING:
                return usec_add(UNIT(s)->active_enter_timestamp.monotonic, s->runtime_max_usec);

        case SERVICE_STOP:
        case SERVICE_STOP_SIGTERM:
        case SERVICE_STOP_SIGKILL:
        case SERVICE_STOP_POST:
        case SERVICE_FINAL_SIGTERM:
        case SERVICE_FINAL_SIGKILL:
                return usec_add(UNIT(s)->state_change_timestamp.monotonic, s->timeout_stop_usec);

        case SERVICE_STOP_WATCHDOG:
                return usec_add(UNIT(s)->state_change_timestamp.monotonic, service_timeout_abort_usec(s));

        case SERVICE_AUTO_RESTART:
                return usec_add(UNIT(s)->inactive_enter_timestamp.monotonic, s->restart_usec);

        case SERVICE_CLEANING:
                return usec_add(UNIT(s)->state_change_timestamp.monotonic, s->exec_context.timeout_clean_usec);

        default:
                return USEC_INFINITY;
        }
}