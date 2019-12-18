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
 scalar_t__ IN_SET (char const,char,char) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 scalar_t__ strchr (char const*,char const) ; 

__attribute__((used)) static char *strcpy_backslash_escaped(char *t, const char *s, const char *bad, bool escape_tab_nl) {
        assert(bad);

        for (; *s; s++) {
                if (escape_tab_nl && IN_SET(*s, '\n', '\t')) {
                        *(t++) = '\\';
                        *(t++) = *s == '\n' ? 'n' : 't';
                        continue;
                }

                if (*s == '\\' || strchr(bad, *s))
                        *(t++) = '\\';

                *(t++) = *s;
        }

        return t;
}