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
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  control_pid; } ;
typedef  TYPE_1__ Mount ;
typedef  int /*<<< orphan*/  KillWho ;

/* Variables and functions */
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_kill_common (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int mount_kill(Unit *u, KillWho who, int signo, sd_bus_error *error) {
        Mount *m = MOUNT(u);

        assert(m);

        return unit_kill_common(u, who, signo, -1, m->control_pid, error);
}