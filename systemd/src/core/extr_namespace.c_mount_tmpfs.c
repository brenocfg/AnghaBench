#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ MountEntry ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  errno ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkdir_p_label (int /*<<< orphan*/ ,int) ; 
 scalar_t__ mount (char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mount_entry_options (TYPE_1__ const*) ; 
 int /*<<< orphan*/  mount_entry_path (TYPE_1__ const*) ; 
 int /*<<< orphan*/  umount_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_tmpfs(const MountEntry *m) {
        assert(m);

        /* First, get rid of everything that is below if there is anything. Then, overmount with our new tmpfs */

        (void) mkdir_p_label(mount_entry_path(m), 0755);
        (void) umount_recursive(mount_entry_path(m), 0);

        if (mount("tmpfs", mount_entry_path(m), "tmpfs", m->flags, mount_entry_options(m)) < 0)
                return log_debug_errno(errno, "Failed to mount %s: %m", mount_entry_path(m));

        return 1;
}