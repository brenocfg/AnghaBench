#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ audit_fd; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSTEM_SHUTDOWN ; 
 scalar_t__ EPERM ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ audit_log_user_comm_message (scalar_t__,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ errno ; 
 int log_error_errno (int,char*) ; 
 int utmp_put_shutdown () ; 

__attribute__((used)) static int on_shutdown(Context *c) {
        int r = 0, q;

        assert(c);

        /* We started shut-down, so let's write the utmp
         * record and send the audit msg */

#if HAVE_AUDIT
        if (c->audit_fd >= 0)
                if (audit_log_user_comm_message(c->audit_fd, AUDIT_SYSTEM_SHUTDOWN, "", "systemd-update-utmp", NULL, NULL, NULL, 1) < 0 &&
                    errno != EPERM) {
                        r = log_error_errno(errno, "Failed to send audit message: %m");
                }
#endif

        q = utmp_put_shutdown();
        if (q < 0) {
                log_error_errno(q, "Failed to write utmp record: %m");
                r = q;
        }

        return r;
}