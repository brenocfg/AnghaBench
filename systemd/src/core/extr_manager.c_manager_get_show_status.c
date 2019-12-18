#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  show_status; scalar_t__ no_console_output; } ;
typedef  scalar_t__ StatusType ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  MANAGER_INITIALIZING ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  MANAGER_STARTING ; 
 int /*<<< orphan*/  MANAGER_STOPPING ; 
 int /*<<< orphan*/  SHOW_STATUS_TEMPORARY ; 
 int /*<<< orphan*/  SHOW_STATUS_YES ; 
 scalar_t__ STATUS_TYPE_EMERGENCY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ manager_check_ask_password (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_state (TYPE_1__*) ; 

__attribute__((used)) static bool manager_get_show_status(Manager *m, StatusType type) {
        assert(m);

        if (!MANAGER_IS_SYSTEM(m))
                return false;

        if (m->no_console_output)
                return false;

        if (!IN_SET(manager_state(m), MANAGER_INITIALIZING, MANAGER_STARTING, MANAGER_STOPPING))
                return false;

        /* If we cannot find out the status properly, just proceed. */
        if (type != STATUS_TYPE_EMERGENCY && manager_check_ask_password(m) > 0)
                return false;

        return IN_SET(m->show_status, SHOW_STATUS_TEMPORARY, SHOW_STATUS_YES);
}