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
struct utmpx {int /*<<< orphan*/  ut_user; int /*<<< orphan*/  ut_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  RUN_LVL ; 
 int /*<<< orphan*/  init_entry (struct utmpx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,int) ; 
 int write_entry_both (struct utmpx*) ; 

int utmp_put_shutdown(void) {
        struct utmpx store = {};

        init_entry(&store, 0);

        store.ut_type = RUN_LVL;
        strncpy(store.ut_user, "shutdown", sizeof(store.ut_user));

        return write_entry_both(&store);
}