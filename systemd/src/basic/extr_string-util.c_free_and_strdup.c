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
 int ENOMEM ; 
 int /*<<< orphan*/  assert (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (char const*) ; 
 scalar_t__ streq_ptr (char*,char const*) ; 

int free_and_strdup(char **p, const char *s) {
        char *t;

        assert(p);

        /* Replaces a string pointer with a strdup()ed new string,
         * possibly freeing the old one. */

        if (streq_ptr(*p, s))
                return 0;

        if (s) {
                t = strdup(s);
                if (!t)
                        return -ENOMEM;
        } else
                t = NULL;

        free(*p);
        *p = t;

        return 1;
}