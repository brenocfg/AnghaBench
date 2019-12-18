#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {scalar_t__ persistent; } ;
typedef  TYPE_1__ Timer ;
typedef  int /*<<< orphan*/  ExecCleanMask ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_CLEAN_STATE ; 
 TYPE_1__* TIMER (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static int timer_can_clean(Unit *u, ExecCleanMask *ret) {
        Timer *t = TIMER(u);

        assert(t);

        *ret = t->persistent ? EXEC_CLEAN_STATE : 0;
        return 0;
}