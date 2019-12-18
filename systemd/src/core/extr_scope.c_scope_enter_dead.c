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
struct TYPE_6__ {scalar_t__ result; } ;
typedef  scalar_t__ ScopeResult ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 int /*<<< orphan*/  SCOPE_DEAD ; 
 int /*<<< orphan*/  SCOPE_FAILED ; 
 scalar_t__ SCOPE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  scope_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  scope_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_result (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_enter_dead(Scope *s, ScopeResult f) {
        assert(s);

        if (s->result == SCOPE_SUCCESS)
                s->result = f;

        unit_log_result(UNIT(s), s->result == SCOPE_SUCCESS, scope_result_to_string(s->result));
        scope_set_state(s, s->result != SCOPE_SUCCESS ? SCOPE_FAILED : SCOPE_DEAD);
}