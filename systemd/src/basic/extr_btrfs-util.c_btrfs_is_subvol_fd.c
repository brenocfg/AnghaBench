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
struct stat {int st_ino; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_is_filesystem (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 

int btrfs_is_subvol_fd(int fd) {
        struct stat st;

        assert(fd >= 0);

        /* On btrfs subvolumes always have the inode 256 */

        if (fstat(fd, &st) < 0)
                return -errno;

        if (!S_ISDIR(st.st_mode) || st.st_ino != 256)
                return 0;

        return btrfs_is_filesystem(fd);
}