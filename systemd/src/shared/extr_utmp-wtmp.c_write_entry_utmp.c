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
struct utmpx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _PATH_UTMPX ; 
 int /*<<< orphan*/  assert (struct utmpx const*) ; 
 int /*<<< orphan*/  endutxent () ; 
 int errno ; 
 int /*<<< orphan*/  pututxline (struct utmpx const*) ; 
 int /*<<< orphan*/  setutxent () ; 
 scalar_t__ utmpxname (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int write_entry_utmp(const struct utmpx *store) {
        int r;

        assert(store);

        /* utmp is similar to wtmp, but there is only one entry for
         * each entry type resp. user; i.e. basically a key/value
         * table. */

        if (utmpxname(_PATH_UTMPX) < 0)
                return -errno;

        setutxent();

        if (!pututxline(store))
                r = -errno;
        else
                r = 0;

        endutxent();

        return r;
}