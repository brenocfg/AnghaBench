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
struct TYPE_5__ {int start_limit_hit; int /*<<< orphan*/  reboot_arg; int /*<<< orphan*/  start_limit_action; int /*<<< orphan*/  manager; int /*<<< orphan*/  id; int /*<<< orphan*/  start_ratelimit; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int ECANCELED ; 
 int EMERGENCY_ACTION_IS_WATCHDOG ; 
 int EMERGENCY_ACTION_WARN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  emergency_action (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  log_unit_warning (TYPE_1__*,char*) ; 
 scalar_t__ ratelimit_below (int /*<<< orphan*/ *) ; 
 char* strjoina (char*,int /*<<< orphan*/ ,char*) ; 

int unit_test_start_limit(Unit *u) {
        const char *reason;

        assert(u);

        if (ratelimit_below(&u->start_ratelimit)) {
                u->start_limit_hit = false;
                return 0;
        }

        log_unit_warning(u, "Start request repeated too quickly.");
        u->start_limit_hit = true;

        reason = strjoina("unit ", u->id, " failed");

        emergency_action(u->manager, u->start_limit_action,
                         EMERGENCY_ACTION_IS_WATCHDOG|EMERGENCY_ACTION_WARN,
                         u->reboot_arg, -1, reason);

        return -ECANCELED;
}