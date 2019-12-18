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
 scalar_t__ IN_SET (char,int /*<<< orphan*/ ,char) ; 
 int /*<<< orphan*/  assert (char*) ; 
 scalar_t__ isempty (char*) ; 
 int path_is_absolute (char*) ; 

char *path_simplify(char *path, bool kill_dots) {
        char *f, *t;
        bool slash = false, ignore_slash = false, absolute;

        assert(path);

        /* Removes redundant inner and trailing slashes. Also removes unnecessary dots
         * if kill_dots is true. Modifies the passed string in-place.
         *
         * ///foo//./bar/.   becomes /foo/./bar/.      (if kill_dots is false)
         * ///foo//./bar/.   becomes /foo/bar          (if kill_dots is true)
         * .//./foo//./bar/. becomes ././foo/./bar/.   (if kill_dots is false)
         * .//./foo//./bar/. becomes foo/bar           (if kill_dots is true)
         */

        if (isempty(path))
                return path;

        absolute = path_is_absolute(path);

        f = path;
        if (kill_dots && *f == '.' && IN_SET(f[1], 0, '/')) {
                ignore_slash = true;
                f++;
        }

        for (t = path; *f; f++) {

                if (*f == '/') {
                        slash = true;
                        continue;
                }

                if (slash) {
                        if (kill_dots && *f == '.' && IN_SET(f[1], 0, '/'))
                                continue;

                        slash = false;
                        if (ignore_slash)
                                ignore_slash = false;
                        else
                                *(t++) = '/';
                }

                *(t++) = *f;
        }

        /* Special rule, if we stripped everything, we either need a "/" (for the root directory)
         * or "." for the current directory */
        if (t == path) {
                if (absolute)
                        *(t++) = '/';
                else
                        *(t++) = '.';
        }

        *t = 0;
        return path;
}