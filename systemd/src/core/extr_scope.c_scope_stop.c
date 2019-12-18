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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Scope ;

/* Variables and functions */
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SCOPE_ABANDONED ; 
 int /*<<< orphan*/  SCOPE_RUNNING ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGKILL ; 
 int /*<<< orphan*/  SCOPE_STOP_SIGTERM ; 
 int /*<<< orphan*/  SCOPE_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  scope_enter_signal (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int scope_stop(Unit *u) {
        Scope *s = SCOPE(u);

        assert(s);

        if (IN_SET(s->state, SCOPE_STOP_SIGTERM, SCOPE_STOP_SIGKILL))
                return 0;

        assert(IN_SET(s->state, SCOPE_RUNNING, SCOPE_ABANDONED));

        scope_enter_signal(s, SCOPE_STOP_SIGTERM, SCOPE_SUCCESS);
        return 1;
}