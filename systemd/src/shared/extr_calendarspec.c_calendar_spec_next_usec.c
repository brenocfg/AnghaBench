#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_10__ {int /*<<< orphan*/  timezone; } ;
struct TYPE_9__ {int return_value; int /*<<< orphan*/  next; } ;
typedef  TYPE_1__ SpecNextResult ;
typedef  TYPE_2__ CalendarSpec ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int FORK_CLOSE_ALL_FDS ; 
 int FORK_DEATHSIG ; 
 int FORK_RESET_SIGNALS ; 
 int FORK_WAIT ; 
 int MAP_ANONYMOUS ; 
 TYPE_1__* MAP_FAILED ; 
 int MAP_SHARED ; 
 int PROT_READ ; 
 int PROT_WRITE ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__ const*) ; 
 int calendar_spec_next_usec_impl (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (int /*<<< orphan*/ ) ; 
 TYPE_1__* mmap (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (TYPE_1__*,int) ; 
 int negative_errno () ; 
 int safe_fork (char*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ setenv (char*,char*,int) ; 
 char* strjoina (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tzset () ; 

int calendar_spec_next_usec(const CalendarSpec *spec, usec_t usec, usec_t *ret_next) {
        SpecNextResult *shared, tmp;
        int r;

        assert(spec);

        if (isempty(spec->timezone))
                return calendar_spec_next_usec_impl(spec, usec, ret_next);

        shared = mmap(NULL, sizeof *shared, PROT_READ|PROT_WRITE, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
        if (shared == MAP_FAILED)
                return negative_errno();

        r = safe_fork("(sd-calendar)", FORK_RESET_SIGNALS|FORK_CLOSE_ALL_FDS|FORK_DEATHSIG|FORK_WAIT, NULL);
        if (r < 0) {
                (void) munmap(shared, sizeof *shared);
                return r;
        }
        if (r == 0) {
                char *colon_tz;

                /* tzset(3) says $TZ should be prefixed with ":" if we reference timezone files */
                colon_tz = strjoina(":", spec->timezone);

                if (setenv("TZ", colon_tz, 1) != 0) {
                        shared->return_value = negative_errno();
                        _exit(EXIT_FAILURE);
                }

                tzset();

                shared->return_value = calendar_spec_next_usec_impl(spec, usec, &shared->next);

                _exit(EXIT_SUCCESS);
        }

        tmp = *shared;
        if (munmap(shared, sizeof *shared) < 0)
                return negative_errno();

        if (tmp.return_value == 0 && ret_next)
                *ret_next = tmp.next;

        return tmp.return_value;
}