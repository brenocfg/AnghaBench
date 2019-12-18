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
typedef  int uint32_t ;
typedef  int uid_t ;
struct stat {int st_uid; int st_gid; } ;
typedef  int gid_t ;

/* Variables and functions */
 int EBADE ; 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int UID_BUSY_BASE ; 
 int UID_BUSY_MASK ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fchown (int,int,int) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int recurse_fd (int,int,struct stat*,int,int) ; 
 int /*<<< orphan*/  safe_close (int) ; 

__attribute__((used)) static int fd_patch_uid_internal(int fd, bool donate_fd, uid_t shift, uid_t range) {
        struct stat st;
        int r;

        assert(fd >= 0);

        /* Recursively adjusts the UID/GIDs of all files of a directory tree. This is used to automatically fix up an
         * OS tree to the used user namespace UID range. Note that this automatic adjustment only works for UID ranges
         * following the concept that the upper 16bit of a UID identify the container, and the lower 16bit are the actual
         * UID within the container. */

        if ((shift & 0xFFFF) != 0) {
                /* We only support containers where the shift starts at a 2^16 boundary */
                r = -EOPNOTSUPP;
                goto finish;
        }

        if (shift == UID_BUSY_BASE) {
                r = -EINVAL;
                goto finish;
        }

        if (range != 0x10000) {
                /* We only support containers with 16bit UID ranges for the patching logic */
                r = -EOPNOTSUPP;
                goto finish;
        }

        if (fstat(fd, &st) < 0) {
                r = -errno;
                goto finish;
        }

        if ((uint32_t) st.st_uid >> 16 != (uint32_t) st.st_gid >> 16) {
                /* We only support containers where the uid/gid container ID match */
                r = -EBADE;
                goto finish;
        }

        /* Try to detect if the range is already right. Of course, this a pretty drastic optimization, as we assume
         * that if the top-level dir has the right upper 16bit assigned, then everything below will have too... */
        if (((uint32_t) (st.st_uid ^ shift) >> 16) == 0)
                return 0;

        /* Before we start recursively chowning, mark the top-level dir as "busy" by chowning it to the "busy"
         * range. Should we be interrupted in the middle of our work, we'll see it owned by this user and will start
         * chown()ing it again, unconditionally, as the busy UID is not a valid UID we'd everpick for ourselves. */

        if ((st.st_uid & UID_BUSY_MASK) != UID_BUSY_BASE) {
                if (fchown(fd,
                           UID_BUSY_BASE | (st.st_uid & ~UID_BUSY_MASK),
                           (gid_t) UID_BUSY_BASE | (st.st_gid & ~(gid_t) UID_BUSY_MASK)) < 0) {
                        r = -errno;
                        goto finish;
                }
        }

        return recurse_fd(fd, donate_fd, &st, shift, true);

finish:
        if (donate_fd)
                safe_close(fd);

        return r;
}