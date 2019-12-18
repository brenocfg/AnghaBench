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
 unsigned int strlen (char const*) ; 

const char *last_path_component(const char *path) {

        /* Finds the last component of the path, preserving the optional trailing slash that signifies a directory.
         *
         *    a/b/c → c
         *    a/b/c/ → c/
         *    x → x
         *    x/ → x/
         *    /y → y
         *    /y/ → y/
         *    / → /
         *    // → /
         *    /foo/a → a
         *    /foo/a/ → a/
         *
         *    Also, the empty string is mapped to itself.
         *
         * This is different than basename(), which returns "" when a trailing slash is present.
         */

        unsigned l, k;

        if (!path)
                return NULL;

        l = k = strlen(path);
        if (l == 0) /* special case — an empty string */
                return path;

        while (k > 0 && path[k-1] == '/')
                k--;

        if (k == 0) /* the root directory */
                return path + l - 1;

        while (k > 0 && path[k-1] != '/')
                k--;

        return path + k;
}