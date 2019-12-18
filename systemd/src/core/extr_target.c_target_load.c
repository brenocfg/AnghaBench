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
struct TYPE_5__ {scalar_t__ load_state; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  Target ;

/* Variables and functions */
 int /*<<< orphan*/ * TARGET (TYPE_1__*) ; 
 scalar_t__ UNIT_LOADED ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int target_add_default_dependencies (int /*<<< orphan*/ *) ; 
 int unit_load_fragment_and_dropin (TYPE_1__*,int) ; 

__attribute__((used)) static int target_load(Unit *u) {
        Target *t = TARGET(u);
        int r;

        assert(t);

        r = unit_load_fragment_and_dropin(u, true);
        if (r < 0)
                return r;

        if (u->load_state != UNIT_LOADED)
                return 0;

        /* This is a new unit? Then let's add in some extras */
        return target_add_default_dependencies(t);
}