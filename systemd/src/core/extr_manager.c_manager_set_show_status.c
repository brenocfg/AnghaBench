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
struct TYPE_6__ {scalar_t__ show_status; } ;
typedef  scalar_t__ ShowStatus ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 TYPE_1__* IN_SET (scalar_t__,int /*<<< orphan*/ ,scalar_t__,...) ; 
 int /*<<< orphan*/  MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  SHOW_STATUS_AUTO ; 
 scalar_t__ SHOW_STATUS_NO ; 
 int /*<<< orphan*/  SHOW_STATUS_TEMPORARY ; 
 int /*<<< orphan*/  SHOW_STATUS_YES ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,char*) ; 
 int /*<<< orphan*/  touch (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void manager_set_show_status(Manager *m, ShowStatus mode) {
        assert(m);
        assert(IN_SET(mode, SHOW_STATUS_AUTO, SHOW_STATUS_NO, SHOW_STATUS_YES, SHOW_STATUS_TEMPORARY));

        if (!MANAGER_IS_SYSTEM(m))
                return;

        if (m->show_status != mode)
                log_debug("%s showing of status.",
                          mode == SHOW_STATUS_NO ? "Disabling" : "Enabling");
        m->show_status = mode;

        if (IN_SET(mode, SHOW_STATUS_TEMPORARY, SHOW_STATUS_YES))
                (void) touch("/run/systemd/show-status");
        else
                (void) unlink("/run/systemd/show-status");
}