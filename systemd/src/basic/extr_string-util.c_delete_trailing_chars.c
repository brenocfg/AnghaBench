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
 char* WHITESPACE ; 
 int /*<<< orphan*/  strchr (char const*,char) ; 

char *delete_trailing_chars(char *s, const char *bad) {
        char *p, *c = s;

        /* Drops all specified bad characters, at the end of the string */

        if (!s)
                return NULL;

        if (!bad)
                bad = WHITESPACE;

        for (p = s; *p; p++)
                if (!strchr(bad, *p))
                        c = p + 1;

        *c = 0;

        return s;
}