#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int perpetual; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_10__ {int /*<<< orphan*/  deserialized_state; } ;
typedef  int /*<<< orphan*/  Slice ;
typedef  char const Manager ;

/* Variables and functions */
 TYPE_7__* SLICE (TYPE_1__*) ; 
 int /*<<< orphan*/  SLICE_ACTIVE ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int log_error_errno (int,char*,char const*) ; 
 TYPE_1__* manager_get_unit (char const*,char const*) ; 
 int /*<<< orphan*/  unit_add_to_dbus_queue (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_add_to_load_queue (TYPE_1__*) ; 
 int unit_new_for_name (char const*,int,char const*,TYPE_1__**) ; 

__attribute__((used)) static int slice_make_perpetual(Manager *m, const char *name, Unit **ret) {
        Unit *u;
        int r;

        assert(m);
        assert(name);

        u = manager_get_unit(m, name);
        if (!u) {
                r = unit_new_for_name(m, sizeof(Slice), name, &u);
                if (r < 0)
                        return log_error_errno(r, "Failed to allocate the special %s unit: %m", name);
        }

        u->perpetual = true;
        SLICE(u)->deserialized_state = SLICE_ACTIVE;

        unit_add_to_load_queue(u);
        unit_add_to_dbus_queue(u);

        if (ret)
                *ret = u;

        return 0;
}