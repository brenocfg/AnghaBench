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
struct btrfs_ioctl_ino_lookup_args {int /*<<< orphan*/  treeid; int /*<<< orphan*/  objectid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FIRST_FREE_OBJECTID ; 
 int /*<<< orphan*/  BTRFS_IOC_INO_LOOKUP ; 
 int ENOTTY ; 
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_is_filesystem (int) ; 
 int errno ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,struct btrfs_ioctl_ino_lookup_args*) ; 

int btrfs_subvol_get_id_fd(int fd, uint64_t *ret) {
        struct btrfs_ioctl_ino_lookup_args args = {
                .objectid = BTRFS_FIRST_FREE_OBJECTID
        };
        int r;

        assert(fd >= 0);
        assert(ret);

        r = btrfs_is_filesystem(fd);
        if (r < 0)
                return r;
        if (!r)
                return -ENOTTY;

        if (ioctl(fd, BTRFS_IOC_INO_LOOKUP, &args) < 0)
                return -errno;

        *ret = args.treeid;
        return 0;
}