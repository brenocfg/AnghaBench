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
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 
 scalar_t__ streq (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strneq (char const*,char const*,size_t) ; 

__attribute__((used)) static bool env_match(const char *t, const char *pattern) {
        assert(t);
        assert(pattern);

        /* pattern a matches string a
         *         a matches a=
         *         a matches a=b
         *         a= matches a=
         *         a=b matches a=b
         *         a= does not match a
         *         a=b does not match a=
         *         a=b does not match a
         *         a=b does not match a=c */

        if (streq(t, pattern))
                return true;

        if (!strchr(pattern, '=')) {
                size_t l = strlen(pattern);

                return strneq(t, pattern, l) && t[l] == '=';
        }

        return false;
}