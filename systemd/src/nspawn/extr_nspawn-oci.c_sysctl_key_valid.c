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
 scalar_t__ isempty (char const*) ; 

__attribute__((used)) static bool sysctl_key_valid(const char *s) {
        bool dot = true;

        /* Note that we are a bit stricter here than in systemd-sysctl, as that inherited semantics from the old sysctl
         * tool, which were really weird (as it swaps / and . in both ways) */

        if (isempty(s))
                return false;

        for (; *s; s++) {

                if (*s <= ' ' || *s >= 127)
                        return false;
                if (*s == '/')
                        return false;
                if (*s == '.') {

                        if (dot) /* Don't allow two dots next to each other (or at the beginning) */
                                return false;

                        dot = true;
                } else
                        dot = false;
        }

        if (dot) /* don't allow a dot at the end */
                return false;

        return true;
}