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
typedef  int /*<<< orphan*/  SleepConfig ;

/* Variables and functions */
 int ENOSPC ; 
 int /*<<< orphan*/  STR_IN_SET (char const*,char*,char*,char*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int can_s2h (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  can_sleep_disk (char**) ; 
 int /*<<< orphan*/  can_sleep_state (char**) ; 
 int /*<<< orphan*/  enough_swap_for_hibernation () ; 
 int /*<<< orphan*/  log_debug (char*,char const*) ; 
 int sleep_settings (char const*,int /*<<< orphan*/  const*,int*,char***,char***) ; 
 scalar_t__ streq (char const*,char*) ; 

__attribute__((used)) static int can_sleep_internal(const char *verb, bool check_allowed, const SleepConfig *sleep_config) {
        bool allow;
        char **modes = NULL, **states = NULL;
        int r;

        assert(STR_IN_SET(verb, "suspend", "hibernate", "hybrid-sleep", "suspend-then-hibernate"));

        r = sleep_settings(verb, sleep_config, &allow, &modes, &states);
        if (r < 0)
                return false;

        if (check_allowed && !allow) {
                log_debug("Sleep mode \"%s\" is disabled by configuration.", verb);
                return false;
        }

        if (streq(verb, "suspend-then-hibernate"))
                return can_s2h(sleep_config);

        if (!can_sleep_state(states) || !can_sleep_disk(modes))
                return false;

        if (streq(verb, "suspend"))
                return true;

        if (!enough_swap_for_hibernation())
                return -ENOSPC;

        return true;
}