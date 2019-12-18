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
struct TYPE_5__ {int on_console; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_ref_console (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_unref_console (int /*<<< orphan*/ ) ; 
 int unit_needs_console (TYPE_1__*) ; 

__attribute__((used)) static void unit_update_on_console(Unit *u) {
        bool b;

        assert(u);

        b = unit_needs_console(u);
        if (u->on_console == b)
                return;

        u->on_console = b;
        if (b)
                manager_ref_console(u->manager);
        else
                manager_unref_console(u->manager);
}