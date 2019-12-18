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
struct utmpx {int ut_pid; int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_type; } ;

/* Variables and functions */
 int ESRCH ; 
 int /*<<< orphan*/  RUN_LVL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  init_entry (struct utmpx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int utmp_get_runlevel (int*,int /*<<< orphan*/ *) ; 
 int write_entry_both (struct utmpx*) ; 

int utmp_put_runlevel(int runlevel, int previous) {
        struct utmpx store = {};
        int r;

        assert(runlevel > 0);

        if (previous <= 0) {
                /* Find the old runlevel automatically */

                r = utmp_get_runlevel(&previous, NULL);
                if (r < 0) {
                        if (r != -ESRCH)
                                return r;

                        previous = 0;
                }
        }

        if (previous == runlevel)
                return 0;

        init_entry(&store, 0);

        store.ut_type = RUN_LVL;
        store.ut_pid = (runlevel & 0xFF) | ((previous & 0xFF) << 8);
        strncpy(store.ut_user, "runlevel", sizeof(store.ut_user));

        return write_entry_both(&store);
}