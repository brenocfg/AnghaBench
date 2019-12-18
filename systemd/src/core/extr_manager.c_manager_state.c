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
struct TYPE_7__ {int /*<<< orphan*/  failed_units; } ;
typedef  int /*<<< orphan*/  ManagerState ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_DEGRADED ; 
 int /*<<< orphan*/  MANAGER_INITIALIZING ; 
 int /*<<< orphan*/  MANAGER_IS_FINISHED (TYPE_1__*) ; 
 scalar_t__ MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  MANAGER_MAINTENANCE ; 
 int /*<<< orphan*/  MANAGER_RUNNING ; 
 int /*<<< orphan*/  MANAGER_STARTING ; 
 int /*<<< orphan*/  MANAGER_STOPPING ; 
 int /*<<< orphan*/  SPECIAL_BASIC_TARGET ; 
 int /*<<< orphan*/  SPECIAL_EMERGENCY_TARGET ; 
 int /*<<< orphan*/  SPECIAL_RESCUE_TARGET ; 
 int /*<<< orphan*/  SPECIAL_SHUTDOWN_TARGET ; 
 int /*<<< orphan*/  UNIT_IS_ACTIVE_OR_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/ * manager_get_unit (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_size (int /*<<< orphan*/ ) ; 
 scalar_t__ unit_active_or_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_active_state (int /*<<< orphan*/ *) ; 

ManagerState manager_state(Manager *m) {
        Unit *u;

        assert(m);

        /* Did we ever finish booting? If not then we are still starting up */
        if (!MANAGER_IS_FINISHED(m)) {

                u = manager_get_unit(m, SPECIAL_BASIC_TARGET);
                if (!u || !UNIT_IS_ACTIVE_OR_RELOADING(unit_active_state(u)))
                        return MANAGER_INITIALIZING;

                return MANAGER_STARTING;
        }

        /* Is the special shutdown target active or queued? If so, we are in shutdown state */
        u = manager_get_unit(m, SPECIAL_SHUTDOWN_TARGET);
        if (u && unit_active_or_pending(u))
                return MANAGER_STOPPING;

        if (MANAGER_IS_SYSTEM(m)) {
                /* Are the rescue or emergency targets active or queued? If so we are in maintenance state */
                u = manager_get_unit(m, SPECIAL_RESCUE_TARGET);
                if (u && unit_active_or_pending(u))
                        return MANAGER_MAINTENANCE;

                u = manager_get_unit(m, SPECIAL_EMERGENCY_TARGET);
                if (u && unit_active_or_pending(u))
                        return MANAGER_MAINTENANCE;
        }

        /* Are there any failed units? If so, we are in degraded mode */
        if (set_size(m->failed_units) > 0)
                return MANAGER_DEGRADED;

        return MANAGER_RUNNING;
}