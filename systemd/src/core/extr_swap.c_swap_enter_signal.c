#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ send_sigkill; } ;
struct TYPE_10__ {scalar_t__ result; TYPE_2__ kill_context; int /*<<< orphan*/  timeout_usec; int /*<<< orphan*/  control_pid; } ;
typedef  int /*<<< orphan*/  SwapState ;
typedef  scalar_t__ SwapResult ;
typedef  TYPE_1__ Swap ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  SWAP_DEACTIVATING_SIGKILL ; 
 int /*<<< orphan*/  SWAP_DEACTIVATING_SIGTERM ; 
 scalar_t__ SWAP_FAILURE_RESOURCES ; 
 scalar_t__ SWAP_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_kill_operation (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int swap_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_enter_dead_or_active (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  swap_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int unit_kill_context (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swap_enter_signal(Swap *s, SwapState state, SwapResult f) {
        int r;

        assert(s);

        if (s->result == SWAP_SUCCESS)
                s->result = f;

        r = unit_kill_context(UNIT(s),
                              &s->kill_context,
                              state_to_kill_operation(s, state),
                              -1,
                              s->control_pid,
                              false);
        if (r < 0)
                goto fail;

        if (r > 0) {
                r = swap_arm_timer(s, usec_add(now(CLOCK_MONOTONIC), s->timeout_usec));
                if (r < 0)
                        goto fail;

                swap_set_state(s, state);
        } else if (state == SWAP_DEACTIVATING_SIGTERM && s->kill_context.send_sigkill)
                swap_enter_signal(s, SWAP_DEACTIVATING_SIGKILL, SWAP_SUCCESS);
        else
                swap_enter_dead_or_active(s, SWAP_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to kill processes: %m");
        swap_enter_dead_or_active(s, SWAP_FAILURE_RESOURCES);
}