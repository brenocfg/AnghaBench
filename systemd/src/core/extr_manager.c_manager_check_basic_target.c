#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_7__ {scalar_t__ taint_logged; scalar_t__ ready_sent; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  SPECIAL_BASIC_TARGET ; 
 int /*<<< orphan*/  UNIT_IS_ACTIVE_OR_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_taint_string (TYPE_1__*) ; 
 int /*<<< orphan*/ * manager_get_unit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_send_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_active_state (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void manager_check_basic_target(Manager *m) {
        Unit *u;

        assert(m);

        /* Small shortcut */
        if (m->ready_sent && m->taint_logged)
                return;

        u = manager_get_unit(m, SPECIAL_BASIC_TARGET);
        if (!u || !UNIT_IS_ACTIVE_OR_RELOADING(unit_active_state(u)))
                return;

        /* For user managers, send out READY=1 as soon as we reach basic.target */
        manager_send_ready(m);

        /* Log the taint string as soon as we reach basic.target */
        log_taint_string(m);
}