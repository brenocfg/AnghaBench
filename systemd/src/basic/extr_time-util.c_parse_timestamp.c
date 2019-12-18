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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_5__ {int return_value; int /*<<< orphan*/  usec; } ;
typedef  TYPE_1__ ParseTimestampResult ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int FORK_CLOSE_ALL_FDS ; 
 int FORK_DEATHSIG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_WAIT ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int MAP_ANONYMOUS ; 
 TYPE_1__* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  STR_IN_SET (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 scalar_t__ endswith_no_case (char const*,char*) ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (TYPE_1__*,int) ; 
 int negative_errno () ; 
 int parse_timestamp_impl (char const*,int /*<<< orphan*/ *,int) ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 char* strjoina (char*,char*) ; 
 char* strndupa (char const*,int) ; 
 char* strrchr (char const*,char) ; 
 scalar_t__ timezone_is_valid (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * tzname ; 
 int /*<<< orphan*/  tzset () ; 

int parse_timestamp(const char *t, usec_t *usec) {
        char *last_space, *tz = NULL;
        ParseTimestampResult *shared, tmp;
        int r;

        last_space = strrchr(t, ' ');
        if (last_space != NULL && timezone_is_valid(last_space + 1, LOG_DEBUG))
                tz = last_space + 1;

        if (!tz || endswith_no_case(t, " UTC"))
                return parse_timestamp_impl(t, usec, false);

        shared = mmap(NULL, sizeof *shared, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
        if (shared == MAP_FAILED)
                return negative_errno();

        r = safe_fork("(sd-timestamp)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_DEATHSIG|FORK_WAIT, NULL);
        if (r < 0) {
                (void) munmap(shared, sizeof *shared);
                return r;
        }
        if (r == 0) {
                bool with_tz = true;
                char *colon_tz;

                /* tzset(3) says $TZ should be prefixed with ":" if we reference timezone files */
                colon_tz = strjoina(":", tz);

                if (setenv("TZ", colon_tz, 1) != 0) {
                        shared->return_value = negative_errno();
                        _exit(EXIT_FAILURE);
                }

                tzset();

                /* If there is a timezone that matches the tzname fields, leave the parsing to the implementation.
                 * Otherwise just cut it off. */
                with_tz = !STR_IN_SET(tz, tzname[0], tzname[1]);

                /* Cut off the timezone if we don't need it. */
                if (with_tz)
                        t = strndupa(t, last_space - t);

                shared->return_value = parse_timestamp_impl(t, &shared->usec, with_tz);

                _exit(EXIT_SUCCESS);
        }

        tmp = *shared;
        if (munmap(shared, sizeof *shared) != 0)
                return negative_errno();

        if (tmp.return_value == 0 && usec)
                *usec = tmp.usec;

        return tmp.return_value;
}