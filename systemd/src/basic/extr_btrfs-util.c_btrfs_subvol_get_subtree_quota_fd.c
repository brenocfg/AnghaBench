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
typedef  int /*<<< orphan*/  BtrfsQuotaInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_qgroup_get_quota_fd (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int btrfs_subvol_find_subtree_qgroup (int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int btrfs_subvol_get_subtree_quota_fd(int fd, uint64_t subvol_id, BtrfsQuotaInfo *ret) {
        uint64_t qgroupid;
        int r;

        assert(fd >= 0);
        assert(ret);

        /* This determines the quota data of the qgroup with the
         * lowest level, that shares the id part with the specified
         * subvolume. This is useful for determining the quota data
         * for entire subvolume subtrees, as long as the subtrees have
         * been set up with btrfs_qgroup_subvol_auto_fd() or in a
         * compatible way */

        r = btrfs_subvol_find_subtree_qgroup(fd, subvol_id, &qgroupid);
        if (r < 0)
                return r;

        return btrfs_qgroup_get_quota_fd(fd, qgroupid, ret);
}