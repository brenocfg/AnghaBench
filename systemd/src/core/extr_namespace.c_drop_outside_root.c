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
typedef  size_t MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (size_t*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_entry_done (size_t*) ; 
 int /*<<< orphan*/  mount_entry_path (size_t*) ; 
 int /*<<< orphan*/  path_startswith (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static void drop_outside_root(const char *root_directory, MountEntry *m, size_t *n) {
        MountEntry *f, *t;

        assert(m);
        assert(n);

        /* Nothing to do */
        if (!root_directory)
                return;

        /* Drops all mounts that are outside of the root directory. */

        for (f = m, t = m; f < m + *n; f++) {

                if (!path_startswith(mount_entry_path(f), root_directory)) {
                        log_debug("%s is outside of root directory.", mount_entry_path(f));
                        mount_entry_done(f);
                        continue;
                }

                *t = *f;
                t++;
        }

        *n = t - m;
}