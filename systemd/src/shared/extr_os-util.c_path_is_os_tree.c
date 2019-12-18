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
 int ENOENT ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 scalar_t__ laccess (char const*,int /*<<< orphan*/ ) ; 
 int open_os_release (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int path_is_os_tree(const char *path) {
        int r;

        assert(path);

        /* Does the path exist at all? If not, generate an error immediately. This is useful so that a missing root dir
         * always results in -ENOENT, and we can properly distinguish the case where the whole root doesn't exist from
         * the case where just the os-release file is missing. */
        if (laccess(path, F_OK) < 0)
                return -errno;

        /* We use {/etc|/usr/lib}/os-release as flag file if something is an OS */
        r = open_os_release(path, NULL, NULL);
        if (r == -ENOENT) /* We got nothing */
                return 0;
        if (r < 0)
                return r;

        return 1;
}