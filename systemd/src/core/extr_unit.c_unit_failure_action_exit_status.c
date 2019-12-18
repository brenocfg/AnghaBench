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
struct TYPE_5__ {scalar_t__ failure_action_exit_status; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int EBADE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int unit_exit_status (TYPE_1__*) ; 

int unit_failure_action_exit_status(Unit *u) {
        int r;

        assert(u);

        /* Returns the exit status to propagate on failure, or an error if there's nothing to propagate */

        if (u->failure_action_exit_status >= 0)
                return u->failure_action_exit_status;

        r = unit_exit_status(u);
        if (r == -EBADE) /* Exited, but not cleanly (i.e. by signal or such) */
                return 255;

        return r;
}