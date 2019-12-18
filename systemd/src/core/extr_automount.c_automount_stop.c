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
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AUTOMOUNT_RUNNING ; 
 int /*<<< orphan*/  AUTOMOUNT_SUCCESS ; 
 int /*<<< orphan*/  AUTOMOUNT_WAITING ; 
 TYPE_1__* IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  automount_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int automount_stop(Unit *u) {
        Automount *a = AUTOMOUNT(u);

        assert(a);
        assert(IN_SET(a->state, AUTOMOUNT_WAITING, AUTOMOUNT_RUNNING));

        automount_enter_dead(a, AUTOMOUNT_SUCCESS);
        return 1;
}