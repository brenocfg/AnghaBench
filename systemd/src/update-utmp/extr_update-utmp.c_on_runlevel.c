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
struct TYPE_5__ {scalar_t__ audit_fd; } ;
typedef  TYPE_1__ Context ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SYSTEM_RUNLEVEL ; 
 int /*<<< orphan*/  ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  ESRCH ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STRLEN (char*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ audit_log_user_comm_message (scalar_t__,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int errno ; 
 int get_current_runlevel (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int log_warning (char*) ; 
 int utmp_get_runlevel (int*,int /*<<< orphan*/ *) ; 
 int utmp_put_runlevel (int,int) ; 
 int /*<<< orphan*/  xsprintf (char*,char*,int,int) ; 

__attribute__((used)) static int on_runlevel(Context *c) {
        int r = 0, q, previous, runlevel;

        assert(c);

        /* We finished changing runlevel, so let's write the
         * utmp record and send the audit msg */

        /* First, get last runlevel */
        q = utmp_get_runlevel(&previous, NULL);

        if (q < 0) {
                if (!IN_SET(q, -ESRCH, -ENOENT))
                        return log_error_errno(q, "Failed to get current runlevel: %m");

                previous = 0;
        }

        /* Secondly, get new runlevel */
        runlevel = get_current_runlevel(c);
        if (runlevel < 0)
                return runlevel;
        if (runlevel == 0)
                return log_warning("Failed to get new runlevel, utmp update skipped.");

        if (previous == runlevel)
                return 0;

#if HAVE_AUDIT
        if (c->audit_fd >= 0) {
                char s[STRLEN("old-level=_ new-level=_") + 1];

                xsprintf(s, "old-level=%c new-level=%c",
                         previous > 0 ? previous : 'N',
                         runlevel);

                if (audit_log_user_comm_message(c->audit_fd, AUDIT_SYSTEM_RUNLEVEL, s,
                                                "systemd-update-utmp", NULL, NULL, NULL, 1) < 0 && errno != EPERM)
                        r = log_error_errno(errno, "Failed to send audit message: %m");
        }
#endif

        q = utmp_put_runlevel(runlevel, previous);
        if (q < 0 && !IN_SET(q, -ESRCH, -ENOENT))
                return log_error_errno(q, "Failed to write utmp record: %m");

        return r;
}