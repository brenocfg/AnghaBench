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
typedef  int /*<<< orphan*/  BtrfsRemoveFlags ;

/* Variables and functions */
 int subvol_remove_children (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int btrfs_subvol_remove_fd(int fd, const char *subvolume, BtrfsRemoveFlags flags) {
        return subvol_remove_children(fd, subvolume, 0, flags);
}