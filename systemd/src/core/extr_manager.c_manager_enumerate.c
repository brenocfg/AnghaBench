#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UnitType ;
struct TYPE_8__ {int /*<<< orphan*/  (* enumerate ) (TYPE_1__*) ;} ;
struct TYPE_7__ {scalar_t__ test_run_flags; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ MANAGER_TEST_RUN_MINIMAL ; 
 size_t _UNIT_TYPE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_dispatch_load_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_type_supported (size_t) ; 
 int /*<<< orphan*/  unit_type_to_string (size_t) ; 
 TYPE_2__** unit_vtable ; 

__attribute__((used)) static void manager_enumerate(Manager *m) {
        UnitType c;

        assert(m);

        if (m->test_run_flags == MANAGER_TEST_RUN_MINIMAL)
                return;

        /* Let's ask every type to load all units from disk/kernel that it might know */
        for (c = 0; c < _UNIT_TYPE_MAX; c++) {
                if (!unit_type_supported(c)) {
                        log_debug("Unit type .%s is not supported on this system.", unit_type_to_string(c));
                        continue;
                }

                if (unit_vtable[c]->enumerate)
                        unit_vtable[c]->enumerate(m);
        }

        manager_dispatch_load_queue(m);
}