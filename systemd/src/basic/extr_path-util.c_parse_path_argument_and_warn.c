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
 scalar_t__ empty_or_root (char*) ; 
 int /*<<< orphan*/  free_and_replace (char*,char*) ; 
 scalar_t__ isempty (char const*) ; 
 int log_error_errno (int,char*,char const*) ; 
 char* mfree (char*) ; 
 int path_make_absolute_cwd (char const*,char**) ; 
 int /*<<< orphan*/  path_simplify (char*,int) ; 

int parse_path_argument_and_warn(const char *path, bool suppress_root, char **arg) {
        char *p;
        int r;

        /*
         * This function is intended to be used in command line
         * parsers, to handle paths that are passed in. It makes the
         * path absolute, and reduces it to NULL if omitted or
         * root (the latter optionally).
         *
         * NOTE THAT THIS WILL FREE THE PREVIOUS ARGUMENT POINTER ON
         * SUCCESS! Hence, do not pass in uninitialized pointers.
         */

        if (isempty(path)) {
                *arg = mfree(*arg);
                return 0;
        }

        r = path_make_absolute_cwd(path, &p);
        if (r < 0)
                return log_error_errno(r, "Failed to parse path \"%s\" and make it absolute: %m", path);

        path_simplify(p, false);
        if (suppress_root && empty_or_root(p))
                p = mfree(p);

        free_and_replace(*arg, p);

        return 0;
}