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
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTOMOUNT_DEAD ; 
 scalar_t__ AUTOMOUNT_FAILED ; 
 int /*<<< orphan*/  AUTOMOUNT_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  automount_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void automount_reset_failed(Unit *u) {
        Automount *a = AUTOMOUNT(u);

        assert(a);

        if (a->state == AUTOMOUNT_FAILED)
                automount_set_state(a, AUTOMOUNT_DEAD);

        a->result = AUTOMOUNT_SUCCESS;
}