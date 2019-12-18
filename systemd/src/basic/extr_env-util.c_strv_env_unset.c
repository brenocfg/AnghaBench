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
 scalar_t__ env_match (char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 

char **strv_env_unset(char **l, const char *p) {

        char **f, **t;

        if (!l)
                return NULL;

        assert(p);

        /* Drops every occurrence of the env var setting p in the
         * string list. Edits in-place. */

        for (f = t = l; *f; f++) {

                if (env_match(*f, p)) {
                        free(*f);
                        continue;
                }

                *(t++) = *f;
        }

        *t = NULL;
        return l;
}