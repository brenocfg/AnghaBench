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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {scalar_t__ type; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ Image ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int EROFS ; 
 scalar_t__ IMAGE_IS_HOST (TYPE_1__*) ; 
 scalar_t__ IMAGE_IS_VENDOR (TYPE_1__*) ; 
 scalar_t__ IMAGE_SUBVOLUME ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  btrfs_qgroup_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_subvol_auto_qgroup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int btrfs_subvol_set_subtree_quota_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int image_set_limit(Image *i, uint64_t referenced_max) {
        assert(i);

        if (IMAGE_IS_VENDOR(i) || IMAGE_IS_HOST(i))
                return -EROFS;

        if (i->type != IMAGE_SUBVOLUME)
                return -EOPNOTSUPP;

        /* We set the quota both for the subvolume as well as for the
         * subtree. The latter is mostly for historical reasons, since
         * we didn't use to have a concept of subtree quota, and hence
         * only modified the subvolume quota. */

        (void) btrfs_qgroup_set_limit(i->path, 0, referenced_max);
        (void) btrfs_subvol_auto_qgroup(i->path, 0, true);
        return btrfs_subvol_set_subtree_quota_limit(i->path, 0, referenced_max);
}