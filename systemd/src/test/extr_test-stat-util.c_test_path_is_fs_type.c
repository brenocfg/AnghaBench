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
 int /*<<< orphan*/  AT_SYMLINK_FOLLOW ; 
 int /*<<< orphan*/  BTRFS_SUPER_MAGIC ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  PROC_SUPER_MAGIC ; 
 int /*<<< orphan*/  TMPFS_MAGIC ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  path_is_fs_type (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ path_is_mount_point (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_path_is_fs_type(void) {
        /* run might not be a mount point in build chroots */
        if (path_is_mount_point("/run", NULL, AT_SYMLINK_FOLLOW) > 0) {
                assert_se(path_is_fs_type("/run", TMPFS_MAGIC) > 0);
                assert_se(path_is_fs_type("/run", BTRFS_SUPER_MAGIC) == 0);
        }
        assert_se(path_is_fs_type("/proc", PROC_SUPER_MAGIC) > 0);
        assert_se(path_is_fs_type("/proc", BTRFS_SUPER_MAGIC) == 0);
        assert_se(path_is_fs_type("/i-dont-exist", BTRFS_SUPER_MAGIC) == -ENOENT);
}