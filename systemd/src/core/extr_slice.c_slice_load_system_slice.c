#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int perpetual; int default_dependencies; scalar_t__ documentation; scalar_t__ description; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPECIAL_SYSTEM_SLICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ strdup (char*) ; 
 scalar_t__ strv_new (char*) ; 
 int /*<<< orphan*/  unit_has_name (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int slice_load_system_slice(Unit *u) {
        assert(u);

        if (!MANAGER_IS_SYSTEM(u->manager))
                return 0;
        if (!unit_has_name(u, SPECIAL_SYSTEM_SLICE))
                return 0;

        u->perpetual = true;

        /* The system slice is a bit special. For example it is always running and cannot be terminated. Because of its
         * special semantics we synthesize it here, instead of relying on the unit file on disk. */

        u->default_dependencies = false;

        if (!u->description)
                u->description = strdup("System Slice");
        if (!u->documentation)
                u->documentation = strv_new("man:systemd.special(7)");

        return 1;
}