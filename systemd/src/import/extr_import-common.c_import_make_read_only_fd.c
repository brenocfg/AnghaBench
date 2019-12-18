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
struct stat {int st_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOTDIR ; 
 int /*<<< orphan*/  ENOTTY ; 
 scalar_t__ IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int btrfs_subvol_set_read_only_fd (int,int) ; 
 int errno ; 
 scalar_t__ fchmod (int,int) ; 
 int fstat (int,struct stat*) ; 
 int log_error_errno (int,char*) ; 

int import_make_read_only_fd(int fd) {
        int r;

        assert(fd >= 0);

        /* First, let's make this a read-only subvolume if it refers
         * to a subvolume */
        r = btrfs_subvol_set_read_only_fd(fd, true);
        if (IN_SET(r, -ENOTTY, -ENOTDIR, -EINVAL)) {
                struct stat st;

                /* This doesn't refer to a subvolume, or the file
                 * system isn't even btrfs. In that, case fall back to
                 * chmod()ing */

                r = fstat(fd, &st);
                if (r < 0)
                        return log_error_errno(errno, "Failed to stat temporary image: %m");

                /* Drop "w" flag */
                if (fchmod(fd, st.st_mode & 07555) < 0)
                        return log_error_errno(errno, "Failed to chmod() final image: %m");

                return 0;

        } else if (r < 0)
                return log_error_errno(r, "Failed to make subvolume read-only: %m");

        return 0;
}