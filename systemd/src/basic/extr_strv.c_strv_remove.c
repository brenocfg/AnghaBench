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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ streq (char*,char const*) ; 

char **strv_remove(char **l, const char *s) {
        char **f, **t;

        if (!l)
                return NULL;

        assert(s);

        /* Drops every occurrence of s in the string list, edits
         * in-place. */

        for (f = t = l; *f; f++)
                if (streq(*f, s))
                        free(*f);
                else
                        *(t++) = *f;

        *t = NULL;
        return l;
}