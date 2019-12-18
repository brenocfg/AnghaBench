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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCOPE_DEAD ; 
 scalar_t__ SCOPE_FAILED ; 
 int /*<<< orphan*/  SCOPE_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  scope_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_reset_failed(Unit *u) {
        Scope *s = SCOPE(u);

        assert(s);

        if (s->state == SCOPE_FAILED)
                scope_set_state(s, SCOPE_DEAD);

        s->result = SCOPE_SUCCESS;
}