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
 scalar_t__ strchr (char const*,char) ; 

char *delete_chars(char *s, const char *bad) {
        char *f, *t;

        /* Drops all specified bad characters, regardless where in the string */

        if (!s)
                return NULL;

        if (!bad)
                bad = WHITESPACE;

        for (f = s, t = s; *f; f++) {
                if (strchr(bad, *f))
                        continue;

                *(t++) = *f;
        }

        *t = 0;

        return s;
}