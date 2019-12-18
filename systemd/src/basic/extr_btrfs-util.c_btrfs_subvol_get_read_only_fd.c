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
typedef  int uint64_t ;
struct stat {int st_ino; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_IOC_SUBVOL_GETFLAGS ; 
 int BTRFS_SUBVOL_RDONLY ; 
 int EINVAL ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int*) ; 

int btrfs_subvol_get_read_only_fd(int fd) {
        uint64_t flags;
        struct stat st;

        assert(fd >= 0);

        if (fstat(fd, &st) < 0)
                return -errno;

        if (!S_ISDIR(st.st_mode) || st.st_ino != 256)
                return -EINVAL;

        if (ioctl(fd, BTRFS_IOC_SUBVOL_GETFLAGS, &flags) < 0)
                return -errno;

        return !!(flags & BTRFS_SUBVOL_RDONLY);
}