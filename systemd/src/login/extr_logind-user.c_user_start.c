#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int started; int stopping; int /*<<< orphan*/  timestamp; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ User ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dual_timestamp_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dual_timestamp_is_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_save (TYPE_1__*) ; 
 int /*<<< orphan*/  user_save_internal (TYPE_1__*) ; 
 int /*<<< orphan*/  user_send_signal (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_start_service (TYPE_1__*) ; 

int user_start(User *u) {
        assert(u);

        if (u->started && !u->stopping)
                return 0;

        /* If u->stopping is set, the user is marked for removal and service stop-jobs are queued. We have to clear
         * that flag before queueing the start-jobs again. If they succeed, the user object can be re-used just fine
         * (pid1 takes care of job-ordering and proper restart), but if they fail, we want to force another user_stop()
         * so possibly pending units are stopped. */
        u->stopping = false;

        if (!u->started)
                log_debug("Starting services for new user %s.", u->name);

        /* Save the user data so far, because pam_systemd will read the XDG_RUNTIME_DIR out of it while starting up
         * systemd --user.  We need to do user_save_internal() because we have not "officially" started yet. */
        user_save_internal(u);

        /* Start user@UID.service */
        user_start_service(u);

        if (!u->started) {
                if (!dual_timestamp_is_set(&u->timestamp))
                        dual_timestamp_get(&u->timestamp);
                user_send_signal(u, true);
                u->started = true;
        }

        /* Save new user data */
        user_save(u);

        return 0;
}