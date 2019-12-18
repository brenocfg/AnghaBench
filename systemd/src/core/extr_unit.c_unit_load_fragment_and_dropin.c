#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ load_state; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ENOENT ; 
 scalar_t__ UNIT_LOADED ; 
 scalar_t__ UNIT_STUB ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  unit_follow_merge (TYPE_1__*) ; 
 int unit_load_dropin (int /*<<< orphan*/ ) ; 
 int unit_load_fragment (TYPE_1__*) ; 

int unit_load_fragment_and_dropin(Unit *u, bool fragment_required) {
        int r;

        assert(u);

        /* Load a .{service,socket,...} file */
        r = unit_load_fragment(u);
        if (r < 0)
                return r;

        if (u->load_state == UNIT_STUB) {
                if (fragment_required)
                        return -ENOENT;

                u->load_state = UNIT_LOADED;
        }

        /* Load drop-in directory data. If u is an alias, we might be reloading the
         * target unit needlessly. But we cannot be sure which drops-ins have already
         * been loaded and which not, at least without doing complicated book-keeping,
         * so let's always reread all drop-ins. */
        return unit_load_dropin(unit_follow_merge(u));
}