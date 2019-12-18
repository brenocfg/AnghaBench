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
struct stat {int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int ENOTTY ; 
 int /*<<< orphan*/  FS_IOC_GETFLAGS ; 
 int /*<<< orphan*/  FS_IOC_SETFLAGS ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fstat (int,struct stat*) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,unsigned int*) ; 

int chattr_fd(int fd, unsigned value, unsigned mask, unsigned *previous) {
        unsigned old_attr, new_attr;
        struct stat st;

        assert(fd >= 0);

        if (fstat(fd, &st) < 0)
                return -errno;

        /* Explicitly check whether this is a regular file or
         * directory. If it is anything else (such as a device node or
         * fifo), then the ioctl will not hit the file systems but
         * possibly drivers, where the ioctl might have different
         * effects. Notably, DRM is using the same ioctl() number. */

        if (!S_ISDIR(st.st_mode) && !S_ISREG(st.st_mode))
                return -ENOTTY;

        if (mask == 0 && !previous)
                return 0;

        if (ioctl(fd, FS_IOC_GETFLAGS, &old_attr) < 0)
                return -errno;

        new_attr = (old_attr & ~mask) | (value & mask);
        if (new_attr == old_attr) {
                if (previous)
                        *previous = old_attr;
                return 0;
        }

        if (ioctl(fd, FS_IOC_SETFLAGS, &new_attr) < 0)
                return -errno;

        if (previous)
                *previous = old_attr;

        return 1;
}