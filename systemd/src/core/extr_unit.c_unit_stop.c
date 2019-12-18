#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitActiveState ;
struct TYPE_13__ {int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_12__ {int (* stop ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int EALREADY ; 
 int EBADR ; 
 scalar_t__ UNIT_IS_INACTIVE_OR_FAILED (int /*<<< orphan*/ ) ; 
 TYPE_10__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_active_state (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_1__*) ; 
 TYPE_1__* unit_following (TYPE_1__*) ; 

int unit_stop(Unit *u) {
        UnitActiveState state;
        Unit *following;

        assert(u);

        state = unit_active_state(u);
        if (UNIT_IS_INACTIVE_OR_FAILED(state))
                return -EALREADY;

        following = unit_following(u);
        if (following) {
                log_unit_debug(u, "Redirecting stop request from %s to %s.", u->id, following->id);
                return unit_stop(following);
        }

        if (!UNIT_VTABLE(u)->stop)
                return -EBADR;

        unit_add_to_dbus_queue(u);

        return UNIT_VTABLE(u)->stop(u);
}