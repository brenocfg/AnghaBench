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
typedef  int /*<<< orphan*/  BtrfsSnapshotFlags ;

/* Variables and functions */
 int btrfs_subvol_snapshot_fd_full (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int btrfs_subvol_snapshot_fd(int old_fd, const char *new_path, BtrfsSnapshotFlags flags) {
        return btrfs_subvol_snapshot_fd_full(old_fd, new_path, flags, NULL, NULL, NULL);
}