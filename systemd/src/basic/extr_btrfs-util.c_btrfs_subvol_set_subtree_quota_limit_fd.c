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
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_qgroup_set_limit_fd (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int btrfs_subvol_find_subtree_qgroup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_subvol_set_subtree_quota_limit_fd(int fd, uint64_t subvol_id, uint64_t referenced_max) {
        uint64_t qgroupid;
        int r;

        assert(fd >= 0);

        r = btrfs_subvol_find_subtree_qgroup(fd, subvol_id, &qgroupid);
        if (r < 0)
                return r;

        return btrfs_qgroup_set_limit_fd(fd, qgroupid, referenced_max);
}