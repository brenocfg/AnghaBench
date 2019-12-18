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
typedef  scalar_t__ uid_t ;
struct stat {scalar_t__ st_uid; scalar_t__ st_gid; int st_mode; } ;
typedef  int mode_t ;
typedef  scalar_t__ gid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AT_EMPTY_PATH ; 
 int EINVAL ; 
 scalar_t__ GID_INVALID ; 
 int MODE_INVALID ; 
 int S_IFMT ; 
 int /*<<< orphan*/  S_ISLNK (int) ; 
 scalar_t__ UID_INVALID ; 
 int errno ; 
 scalar_t__ fchmod_opath (int,int) ; 
 scalar_t__ fchownat (int,char*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 

int fchmod_and_chown(int fd, mode_t mode, uid_t uid, gid_t gid) {
        bool do_chown, do_chmod;
        struct stat st;

        /* Change ownership and access mode of the specified fd. Tries to do so safely, ensuring that at no
         * point in time the access mode is above the old access mode under the old ownership or the new
         * access mode under the new ownership. Note: this call tries hard to leave the access mode
         * unaffected if the uid/gid is changed, i.e. it undoes implicit suid/sgid dropping the kernel does
         * on chown().
         *
         * This call is happy with O_PATH fds. */

        if (fstat(fd, &st) < 0)
                return -errno;

        do_chown =
                (uid != UID_INVALID && st.st_uid != uid) ||
                (gid != GID_INVALID && st.st_gid != gid);

        do_chmod =
                !S_ISLNK(st.st_mode) && /* chmod is not defined on symlinks */
                ((mode != MODE_INVALID && ((st.st_mode ^ mode) & 07777) != 0) ||
                 do_chown); /* If we change ownership, make sure we reset the mode afterwards, since chown()
                             * modifies the access mode too */

        if (mode == MODE_INVALID)
                mode = st.st_mode; /* If we only shall do a chown(), save original mode, since chown() might break it. */
        else if ((mode & S_IFMT) != 0 && ((mode ^ st.st_mode) & S_IFMT) != 0)
                return -EINVAL; /* insist on the right file type if it was specified */

        if (do_chown && do_chmod) {
                mode_t minimal = st.st_mode & mode; /* the subset of the old and the new mask */

                if (((minimal ^ st.st_mode) & 07777) != 0)
                        if (fchmod_opath(fd, minimal & 07777) < 0)
                                return -errno;
        }

        if (do_chown)
                if (fchownat(fd, "", uid, gid, AT_EMPTY_PATH) < 0)
                        return -errno;

        if (do_chmod)
                if (fchmod_opath(fd, mode & 07777) < 0)
                        return -errno;

        return do_chown || do_chmod;
}