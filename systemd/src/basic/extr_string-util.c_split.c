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
typedef  int SplitFlags ;

/* Variables and functions */
 int SPLIT_QUOTES ; 
 int SPLIT_RELAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strchr (char const*,char const) ; 
 size_t strcspn (char const*,char const*) ; 
 size_t strcspn_escaped (char const*,char const*) ; 
 int /*<<< orphan*/  strspn (char const*,char const*) ; 

const char* split(const char **state, size_t *l, const char *separator, SplitFlags flags) {
        const char *current;

        current = *state;

        if (!*current) {
                assert(**state == '\0');
                return NULL;
        }

        current += strspn(current, separator);
        if (!*current) {
                *state = current;
                return NULL;
        }

        if (flags & SPLIT_QUOTES && strchr("\'\"", *current)) {
                char quotechars[2] = {*current, '\0'};

                *l = strcspn_escaped(current + 1, quotechars);
                if (current[*l + 1] == '\0' || current[*l + 1] != quotechars[0] ||
                    (current[*l + 2] && !strchr(separator, current[*l + 2]))) {
                        /* right quote missing or garbage at the end */
                        if (flags & SPLIT_RELAX) {
                                *state = current + *l + 1 + (current[*l + 1] != '\0');
                                return current + 1;
                        }
                        *state = current;
                        return NULL;
                }
                *state = current++ + *l + 2;
        } else if (flags & SPLIT_QUOTES) {
                *l = strcspn_escaped(current, separator);
                if (current[*l] && !strchr(separator, current[*l]) && !(flags & SPLIT_RELAX)) {
                        /* unfinished escape */
                        *state = current;
                        return NULL;
                }
                *state = current + *l;
        } else {
                *l = strcspn(current, separator);
                *state = current + *l;
        }

        return current;
}