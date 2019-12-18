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
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int btrfs_qgroup_copy_limits (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_subvol_find_subtree_qgroup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copy_subtree_quota_limits(int fd, uint64_t old_subvol, uint64_t new_subvol) {
        uint64_t old_subtree_qgroup, new_subtree_qgroup;
        bool changed;
        int r;

        /* First copy the leaf limits */
        r = btrfs_qgroup_copy_limits(fd, old_subvol, new_subvol);
        if (r < 0)
                return r;
        changed = r > 0;

        /* Then, try to copy the subtree limits, if there are any. */
        r = btrfs_subvol_find_subtree_qgroup(fd, old_subvol, &old_subtree_qgroup);
        if (r < 0)
                return r;
        if (r == 0)
                return changed;

        r = btrfs_subvol_find_subtree_qgroup(fd, new_subvol, &new_subtree_qgroup);
        if (r < 0)
                return r;
        if (r == 0)
                return changed;

        r = btrfs_qgroup_copy_limits(fd, old_subtree_qgroup, new_subtree_qgroup);
        if (r != 0)
                return r;

        return changed;
}