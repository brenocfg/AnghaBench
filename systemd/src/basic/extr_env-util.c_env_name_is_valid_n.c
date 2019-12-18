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

/* Variables and functions */
 int /*<<< orphan*/  VALID_CHARS_ENV_NAME ; 
 int /*<<< orphan*/  _SC_ARG_MAX ; 
 int /*<<< orphan*/  strchr (int /*<<< orphan*/ ,char const) ; 
 scalar_t__ sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool env_name_is_valid_n(const char *e, size_t n) {
        const char *p;

        if (!e)
                return false;

        if (n <= 0)
                return false;

        if (e[0] >= '0' && e[0] <= '9')
                return false;

        /* POSIX says the overall size of the environment block cannot
         * be > ARG_MAX, an individual assignment hence cannot be
         * either. Discounting the equal sign and trailing NUL this
         * hence leaves ARG_MAX-2 as longest possible variable
         * name. */
        if (n > (size_t) sysconf(_SC_ARG_MAX) - 2)
                return false;

        for (p = e; p < e + n; p++)
                if (!strchr(VALID_CHARS_ENV_NAME, *p))
                        return false;

        return true;
}