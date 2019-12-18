#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int (* may_gc ) (int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/ * UNIT_TRIGGER (int /*<<< orphan*/ *) ; 
 TYPE_1__* UNIT_VTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool automount_may_gc(Unit *u) {
        Unit *t;

        assert(u);

        t = UNIT_TRIGGER(u);
        if (!t)
                return true;

        return UNIT_VTABLE(t)->may_gc(t);
}