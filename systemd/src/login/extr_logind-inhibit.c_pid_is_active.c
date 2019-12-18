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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  Session ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int manager_get_session_by_pid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int session_is_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pid_is_active(Manager *m, pid_t pid) {
        Session *s;
        int r;

        /* Get client session.  This is not what you are looking for these days.
         * FIXME #6852 */
        r = manager_get_session_by_pid(m, pid, &s);
        if (r < 0)
                return r;

        /* If there's no session assigned to it, then it's globally
         * active on all ttys */
        if (r == 0)
                return 1;

        return session_is_active(s);
}