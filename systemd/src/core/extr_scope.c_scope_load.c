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
struct TYPE_6__ {scalar_t__ load_state; int /*<<< orphan*/  manager; int /*<<< orphan*/  transient; } ;
typedef  TYPE_1__ Unit ;
typedef  int /*<<< orphan*/  Scope ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MANAGER_IS_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SCOPE (TYPE_1__*) ; 
 scalar_t__ UNIT_LOADED ; 
 scalar_t__ UNIT_STUB ; 
 int /*<<< orphan*/  assert (int) ; 
 int scope_add_extras (int /*<<< orphan*/ *) ; 
 int scope_load_init_scope (TYPE_1__*) ; 
 int scope_verify (int /*<<< orphan*/ *) ; 
 int unit_load_fragment_and_dropin (TYPE_1__*,int) ; 

__attribute__((used)) static int scope_load(Unit *u) {
        Scope *s = SCOPE(u);
        int r;

        assert(s);
        assert(u->load_state == UNIT_STUB);

        if (!u->transient && !MANAGER_IS_RELOADING(u->manager))
                /* Refuse to load non-transient scope units, but allow them while reloading. */
                return -ENOENT;

        r = scope_load_init_scope(u);
        if (r < 0)
                return r;

        r = unit_load_fragment_and_dropin(u, false);
        if (r < 0)
                return r;

        if (u->load_state != UNIT_LOADED)
                return 0;

        r = scope_add_extras(s);
        if (r < 0)
                return r;

        return scope_verify(s);
}