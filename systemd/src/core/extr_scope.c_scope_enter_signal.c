#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ result; int /*<<< orphan*/  timeout_stop_usec; scalar_t__ was_abandoned; int /*<<< orphan*/  kill_context; } ;
typedef  int /*<<< orphan*/  ScopeState ;
typedef  scalar_t__ ScopeResult ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  KILL_KILL ; 
 int /*<<< orphan*/  KILL_TERMINATE ; 
 int /*<<< orphan*/  KILL_TERMINATE_AND_LOG ; 
 scalar_t__ SCOPE_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGTERM ; 
 scalar_t__ SCOPE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ bus_scope_send_request_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int scope_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_enter_dead (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  scope_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_enqueue_rewatch_pids (int /*<<< orphan*/ ) ; 
 int unit_kill_context (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  unit_watch_all_pids (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_enter_signal(Scope *s, ScopeState state, ScopeResult f) {
        bool skip_signal = false;
        int r;

        assert(s);

        if (s->result == SCOPE_SUCCESS)
                s->result = f;

        /* Before sending any signal, make sure we track all members of this cgroup */
        (void) unit_watch_all_pids(UNIT(s));

        /* Also, enqueue a job that we recheck all our PIDs a bit later, given that it's likely some processes have
         * died now */
        (void) unit_enqueue_rewatch_pids(UNIT(s));

        /* If we have a controller set let's ask the controller nicely to terminate the scope, instead of us going
         * directly into SIGTERM berserk mode */
        if (state == SCOPE_STOP_SIGTERM)
                skip_signal = bus_scope_send_request_stop(s) > 0;

        if (skip_signal)
                r = 1; /* wait */
        else {
                r = unit_kill_context(
                                UNIT(s),
                                &s->kill_context,
                                state != SCOPE_STOP_SIGTERM ? KILL_KILL :
                                s->was_abandoned            ? KILL_TERMINATE_AND_LOG :
                                                              KILL_TERMINATE,
                                -1, -1, false);
                if (r < 0)
                        goto fail;
        }

        if (r > 0) {
                r = scope_arm_timer(s, usec_add(now(CLOCK_MONOTONIC), s->timeout_stop_usec));
                if (r < 0)
                        goto fail;

                scope_set_state(s, state);
        } else if (state == SCOPE_STOP_SIGTERM)
                scope_enter_signal(s, SCOPE_STOP_SIGKILL, SCOPE_SUCCESS);
        else
                scope_enter_dead(s, SCOPE_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to kill processes: %m");

        scope_enter_dead(s, SCOPE_FAILURE_RESOURCES);
}