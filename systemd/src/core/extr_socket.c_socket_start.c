#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
struct TYPE_18__ {int reset_accounting; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_20__ {int /*<<< orphan*/  state; } ;
struct TYPE_19__ {int /*<<< orphan*/  exec_command; int /*<<< orphan*/  result; int /*<<< orphan*/  state; int /*<<< orphan*/  service; } ;
struct TYPE_17__ {scalar_t__ load_state; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ Socket ;
typedef  TYPE_3__ Service ;

/* Variables and functions */
 int EAGAIN ; 
 int EBUSY ; 
 int ENOENT ; 
 TYPE_2__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_3__* SERVICE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERVICE_AUTO_RESTART ; 
 int /*<<< orphan*/  SERVICE_DEAD ; 
 int /*<<< orphan*/  SERVICE_FAILED ; 
 TYPE_2__* SOCKET (TYPE_1__*) ; 
 int /*<<< orphan*/  SOCKET_CLEANING ; 
 int /*<<< orphan*/  SOCKET_DEAD ; 
 int /*<<< orphan*/  SOCKET_FAILED ; 
 int /*<<< orphan*/  SOCKET_FAILURE_START_LIMIT_HIT ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_FINAL_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_START_CHOWN ; 
 int /*<<< orphan*/  SOCKET_START_POST ; 
 int /*<<< orphan*/  SOCKET_START_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_POST ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGKILL ; 
 int /*<<< orphan*/  SOCKET_STOP_PRE_SIGTERM ; 
 int /*<<< orphan*/  SOCKET_SUCCESS ; 
 TYPE_11__* UNIT (TYPE_3__*) ; 
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_ISSET (int /*<<< orphan*/ ) ; 
 scalar_t__ UNIT_LOADED ; 
 int /*<<< orphan*/  _SOCKET_EXEC_COMMAND_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  exec_command_reset_status_list_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_error (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_dead (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket_enter_start_pre (TYPE_2__*) ; 
 int unit_acquire_invocation_id (TYPE_1__*) ; 
 int unit_test_start_limit (TYPE_1__*) ; 

__attribute__((used)) static int socket_start(Unit *u) {
        Socket *s = SOCKET(u);
        int r;

        assert(s);

        /* We cannot fulfill this request right now, try again later
         * please! */
        if (IN_SET(s->state,
                   SOCKET_STOP_PRE,
                   SOCKET_STOP_PRE_SIGKILL,
                   SOCKET_STOP_PRE_SIGTERM,
                   SOCKET_STOP_POST,
                   SOCKET_FINAL_SIGTERM,
                   SOCKET_FINAL_SIGKILL,
                   SOCKET_CLEANING))
                return -EAGAIN;

        /* Already on it! */
        if (IN_SET(s->state,
                   SOCKET_START_PRE,
                   SOCKET_START_CHOWN,
                   SOCKET_START_POST))
                return 0;

        /* Cannot run this without the service being around */
        if (UNIT_ISSET(s->service)) {
                Service *service;

                service = SERVICE(UNIT_DEREF(s->service));

                if (UNIT(service)->load_state != UNIT_LOADED) {
                        log_unit_error(u, "Socket service %s not loaded, refusing.", UNIT(service)->id);
                        return -ENOENT;
                }

                /* If the service is already active we cannot start the
                 * socket */
                if (!IN_SET(service->state, SERVICE_DEAD, SERVICE_FAILED, SERVICE_AUTO_RESTART)) {
                        log_unit_error(u, "Socket service %s already active, refusing.", UNIT(service)->id);
                        return -EBUSY;
                }
        }

        assert(IN_SET(s->state, SOCKET_DEAD, SOCKET_FAILED));

        r = unit_test_start_limit(u);
        if (r < 0) {
                socket_enter_dead(s, SOCKET_FAILURE_START_LIMIT_HIT);
                return r;
        }

        r = unit_acquire_invocation_id(u);
        if (r < 0)
                return r;

        s->result = SOCKET_SUCCESS;
        exec_command_reset_status_list_array(s->exec_command, _SOCKET_EXEC_COMMAND_MAX);

        u->reset_accounting = true;

        socket_enter_start_pre(s);
        return 1;
}