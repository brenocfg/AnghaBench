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
struct TYPE_5__ {int /*<<< orphan*/  pids; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  PTR_TO_PID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  set_first (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_unwatch_pid (TYPE_1__*,int /*<<< orphan*/ ) ; 

void unit_unwatch_all_pids(Unit *u) {
        assert(u);

        while (!set_isempty(u->pids))
                unit_unwatch_pid(u, PTR_TO_PID(set_first(u->pids)));

        u->pids = set_free(u->pids);
}