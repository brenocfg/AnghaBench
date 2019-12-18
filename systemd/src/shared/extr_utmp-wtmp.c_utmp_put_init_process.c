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
struct utmpx {int ut_type; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_line; int /*<<< orphan*/  ut_id; int /*<<< orphan*/  ut_session; int /*<<< orphan*/  ut_pid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int INIT_PROCESS ; 
 scalar_t__ IN_SET (int,int,int) ; 
 int LOGIN_PROCESS ; 
 int USER_PROCESS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  copy_suffix (int /*<<< orphan*/ ,int,char const*) ; 
 int /*<<< orphan*/  init_timestamp (struct utmpx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  strncpy_exact (int /*<<< orphan*/ ,char const*,int) ; 
 int write_entry_both (struct utmpx*) ; 

int utmp_put_init_process(const char *id, pid_t pid, pid_t sid, const char *line, int ut_type, const char *user) {
        struct utmpx store = {
                .ut_type = INIT_PROCESS,
                .ut_pid = pid,
                .ut_session = sid,
        };
        int r;

        assert(id);

        init_timestamp(&store, 0);

        /* Copy the whole string if it fits, or just the suffix without the terminating NUL. */
        copy_suffix(store.ut_id, sizeof(store.ut_id), id);

        if (line)
                strncpy_exact(store.ut_line, line, sizeof(store.ut_line));

        r = write_entry_both(&store);
        if (r < 0)
                return r;

        if (IN_SET(ut_type, LOGIN_PROCESS, USER_PROCESS)) {
                store.ut_type = LOGIN_PROCESS;
                r = write_entry_both(&store);
                if (r < 0)
                        return r;
        }

        if (ut_type == USER_PROCESS) {
                store.ut_type = USER_PROCESS;
                strncpy(store.ut_user, user, sizeof(store.ut_user)-1);
                r = write_entry_both(&store);
                if (r < 0)
                        return r;
        }

        return 0;
}