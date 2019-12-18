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
struct TYPE_4__ {int control_pid; } ;
typedef  TYPE_1__ Mount ;

/* Variables and functions */
 TYPE_1__* MOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static int mount_control_pid(Unit *u) {
        Mount *m = MOUNT(u);

        assert(m);

        return m->control_pid;
}