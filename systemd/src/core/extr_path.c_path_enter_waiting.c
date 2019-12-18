#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Path ;

/* Variables and functions */
 int /*<<< orphan*/  PATH_FAILURE_RESOURCES ; 
 int /*<<< orphan*/  PATH_WAITING ; 
 int /*<<< orphan*/  UNIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ path_check_good (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  path_enter_dead (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  path_enter_running (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  path_set_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int path_watch (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void path_enter_waiting(Path *p, bool initial, bool recheck) {
        int r;

        if (recheck)
                if (path_check_good(p, initial)) {
                        log_unit_debug(UNIT(p), "Got triggered.");
                        path_enter_running(p);
                        return;
                }

        r = path_watch(p);
        if (r < 0)
                goto fail;

        /* Hmm, so now we have created inotify watches, but the file
         * might have appeared/been removed by now, so we must
         * recheck */

        if (recheck)
                if (path_check_good(p, false)) {
                        log_unit_debug(UNIT(p), "Got triggered.");
                        path_enter_running(p);
                        return;
                }

        path_set_state(p, PATH_WAITING);
        return;

fail:
        log_unit_warning_errno(UNIT(p), r, "Failed to enter waiting state: %m");
        path_enter_dead(p, PATH_FAILURE_RESOURCES);
}