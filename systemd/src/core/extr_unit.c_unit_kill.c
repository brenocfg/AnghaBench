#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int (* kill ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  KillWho ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int SIGNAL_VALID (int) ; 
 TYPE_1__* UNIT_VTABLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _KILL_WHO_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

int unit_kill(Unit *u, KillWho w, int signo, sd_bus_error *error) {
        assert(u);
        assert(w >= 0 && w < _KILL_WHO_MAX);
        assert(SIGNAL_VALID(signo));

        if (!UNIT_VTABLE(u)->kill)
                return -EOPNOTSUPP;

        return UNIT_VTABLE(u)->kill(u, w, signo, error);
}