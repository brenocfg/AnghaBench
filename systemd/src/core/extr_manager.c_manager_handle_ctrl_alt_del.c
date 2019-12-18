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
struct TYPE_5__ {scalar_t__ cad_burst_action; int /*<<< orphan*/  ctrl_alt_del_ratelimit; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ EMERGENCY_ACTION_NONE ; 
 int /*<<< orphan*/  EMERGENCY_ACTION_WARN ; 
 int /*<<< orphan*/  JOB_REPLACE_IRREVERSIBLY ; 
 int /*<<< orphan*/  SPECIAL_CTRL_ALT_DEL_TARGET ; 
 int /*<<< orphan*/  emergency_action (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  manager_start_target (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ratelimit_below (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void manager_handle_ctrl_alt_del(Manager *m) {
        /* If the user presses C-A-D more than
         * 7 times within 2s, we reboot/shutdown immediately,
         * unless it was disabled in system.conf */

        if (ratelimit_below(&m->ctrl_alt_del_ratelimit) || m->cad_burst_action == EMERGENCY_ACTION_NONE)
                manager_start_target(m, SPECIAL_CTRL_ALT_DEL_TARGET, JOB_REPLACE_IRREVERSIBLY);
        else
                emergency_action(m, m->cad_burst_action, EMERGENCY_ACTION_WARN, NULL, -1,
                                "Ctrl-Alt-Del was pressed more than 7 times within 2s");
}