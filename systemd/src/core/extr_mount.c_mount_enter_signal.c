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
typedef  int /*<<< orphan*/  MountState ;
typedef  scalar_t__ MountResult ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MOUNT_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  MOUNT_REMOUNTING_SIGKILL ; 
 int /*<<< orphan*/  MOUNT_REMOUNTING_SIGTERM ; 
 scalar_t__ MOUNT_SUCCESS ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGKILL ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGTERM ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int mount_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_enter_dead_or_mounted (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mount_enter_mounted (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  state_to_kill_operation (int /*<<< orphan*/ ) ; 
 int unit_kill_context (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mount_enter_signal(Mount *m, MountState state, MountResult f) {
        int r;

        assert(m);

        if (m->result == MOUNT_SUCCESS)
                m->result = f;

        r = unit_kill_context(
                        UNIT(m),
                        &m->kill_context,
                        state_to_kill_operation(state),
                        -1,
                        m->control_pid,
                        false);
        if (r < 0)
                goto fail;

        if (r > 0) {
                r = mount_arm_timer(m, usec_add(now(CLOCK_MONOTONIC), m->timeout_usec));
                if (r < 0)
                        goto fail;

                mount_set_state(m, state);
        } else if (state == MOUNT_REMOUNTING_SIGTERM && m->kill_context.send_sigkill)
                mount_enter_signal(m, MOUNT_REMOUNTING_SIGKILL, MOUNT_SUCCESS);
        else if (IN_SET(state, MOUNT_REMOUNTING_SIGTERM, MOUNT_REMOUNTING_SIGKILL))
                mount_enter_mounted(m, MOUNT_SUCCESS);
        else if (state == MOUNT_UNMOUNTING_SIGTERM && m->kill_context.send_sigkill)
                mount_enter_signal(m, MOUNT_UNMOUNTING_SIGKILL, MOUNT_SUCCESS);
        else
                mount_enter_dead_or_mounted(m, MOUNT_SUCCESS);

        return;

fail:
        log_unit_warning_errno(UNIT(m), r, "Failed to kill processes: %m");
        mount_enter_dead_or_mounted(m, MOUNT_FAILURE_RESOURCES);
}