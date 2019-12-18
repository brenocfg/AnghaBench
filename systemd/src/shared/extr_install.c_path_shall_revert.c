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
typedef  char LookupPaths ;

/* Variables and functions */
 int /*<<< orphan*/  assert (char const*) ; 
 int path_is_config (char const*,char const*,int) ; 
 int path_is_control (char const*,char const*) ; 
 int path_is_transient (char const*,char const*) ; 

__attribute__((used)) static int path_shall_revert(const LookupPaths *paths, const char *path) {
        int r;

        assert(paths);
        assert(path);

        /* Checks whether the path is one where the drop-in directories shall be removed. */

        r = path_is_config(paths, path, true);
        if (r != 0)
                return r;

        r = path_is_control(paths, path);
        if (r != 0)
                return r;

        return path_is_transient(paths, path);
}