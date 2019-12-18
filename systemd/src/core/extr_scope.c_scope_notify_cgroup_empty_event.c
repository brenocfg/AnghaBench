#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCOPE_ABANDONED ; 
 int /*<<< orphan*/  SCOPE_RUNNING ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SCOPE_SUCCESS ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  scope_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_notify_cgroup_empty_event(Unit *u) {
        Scope *s = SCOPE(u);
        assert(u);

        log_unit_debug(u, "cgroup is empty");

        if (IN_SET(s->state, SCOPE_RUNNING, SCOPE_ABANDONED, SCOPE_STOP_SIGTERM, SCOPE_STOP_SIGKILL))
                scope_enter_dead(s, SCOPE_SUCCESS);
}