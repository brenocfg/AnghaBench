#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {scalar_t__ state; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 int EAGAIN ; 
 TYPE_1__* IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MOUNT_CLEANING ; 
 int /*<<< orphan*/  MOUNT_DEAD ; 
 int /*<<< orphan*/  MOUNT_FAILED ; 
 int /*<<< orphan*/  MOUNT_FAILURE_START_LIMIT_HIT ; 
 scalar_t__ MOUNT_MOUNTING ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGKILL ; 
 int /*<<< orphan*/  MOUNT_UNMOUNTING_SIGTERM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_cycle_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  mount_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_enter_mounting (TYPE_1__*) ; 
 int unit_acquire_invocation_id (int /*<<< orphan*/ *) ; 
 int unit_test_start_limit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mount_start(Unit *u) {
        Mount *m = MOUNT(u);
        int r;

        assert(m);

        /* We cannot fulfill this request right now, try again later
         * please! */
        if (IN_SET(m->state,
                   MOUNT_UNMOUNTING,
                   MOUNT_UNMOUNTING_SIGTERM,
                   MOUNT_UNMOUNTING_SIGKILL,
                   MOUNT_CLEANING))
                return -EAGAIN;

        /* Already on it! */
        if (m->state == MOUNT_MOUNTING)
                return 0;

        assert(IN_SET(m->state, MOUNT_DEAD, MOUNT_FAILED));

        r = unit_test_start_limit(u);
        if (r < 0) {
                mount_enter_dead(m, MOUNT_FAILURE_START_LIMIT_HIT);
                return r;
        }

        r = unit_acquire_invocation_id(u);
        if (r < 0)
                return r;

        mount_cycle_clear(m);
        mount_enter_mounting(m);

        return 1;
}