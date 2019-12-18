#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_10__ {scalar_t__ controller; int /*<<< orphan*/  was_abandoned; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Scope ;
typedef  TYPE_1__ FILE ;
typedef  TYPE_1__ FDSet ;

/* Variables and functions */
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ scope_state_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_bool (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serialize_item (TYPE_1__*,char*,scalar_t__) ; 

__attribute__((used)) static int scope_serialize(Unit *u, FILE *f, FDSet *fds) {
        Scope *s = SCOPE(u);

        assert(s);
        assert(f);
        assert(fds);

        (void) serialize_item(f, "state", scope_state_to_string(s->state));
        (void) serialize_bool(f, "was-abandoned", s->was_abandoned);

        if (s->controller)
                (void) serialize_item(f, "controller", s->controller);

        return 0;
}