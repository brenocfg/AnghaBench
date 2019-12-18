#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int e_termination; int e_exit; } ;
struct utmpx {scalar_t__ ut_pid; int /*<<< orphan*/  ut_tv; int /*<<< orphan*/  ut_host; int /*<<< orphan*/  ut_user; TYPE_1__ ut_exit; int /*<<< orphan*/  ut_type; int /*<<< orphan*/  ut_id; } ;
typedef  int /*<<< orphan*/  store_wtmp ;
typedef  int /*<<< orphan*/  store ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEAD_PROCESS ; 
 int /*<<< orphan*/  INIT_PROCESS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  copy_suffix (int /*<<< orphan*/ ,int,char const*) ; 
 struct utmpx* getutxid (struct utmpx*) ; 
 int /*<<< orphan*/  init_timestamp (struct utmpx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct utmpx*,struct utmpx*,int) ; 
 int /*<<< orphan*/  setutxent () ; 
 int write_utmp_wtmp (struct utmpx*,struct utmpx*) ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ ) ; 

int utmp_put_dead_process(const char *id, pid_t pid, int code, int status) {
        struct utmpx lookup = {
                .ut_type = INIT_PROCESS /* looks for DEAD_PROCESS, LOGIN_PROCESS, USER_PROCESS, too */
        }, store, store_wtmp, *found;

        assert(id);

        setutxent();

        /* Copy the whole string if it fits, or just the suffix without the terminating NUL. */
        copy_suffix(store.ut_id, sizeof(store.ut_id), id);

        found = getutxid(&lookup);
        if (!found)
                return 0;

        if (found->ut_pid != pid)
                return 0;

        memcpy(&store, found, sizeof(store));
        store.ut_type = DEAD_PROCESS;
        store.ut_exit.e_termination = code;
        store.ut_exit.e_exit = status;

        zero(store.ut_user);
        zero(store.ut_host);
        zero(store.ut_tv);

        memcpy(&store_wtmp, &store, sizeof(store_wtmp));
        /* wtmp wants the current time */
        init_timestamp(&store_wtmp, 0);

        return write_utmp_wtmp(&store, &store_wtmp);
}