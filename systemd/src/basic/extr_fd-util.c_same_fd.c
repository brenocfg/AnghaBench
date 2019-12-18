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
struct stat {int st_mode; scalar_t__ st_dev; scalar_t__ st_ino; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KCMP_FILE ; 
 int S_IFMT ; 
 scalar_t__ S_ISBLK (int) ; 
 scalar_t__ S_ISCHR (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int /*<<< orphan*/  getpid_cached () ; 
 int kcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

int same_fd(int a, int b) {
        struct stat sta, stb;
        pid_t pid;
        int r, fa, fb;

        assert(a >= 0);
        assert(b >= 0);

        /* Compares two file descriptors. Note that semantics are
         * quite different depending on whether we have kcmp() or we
         * don't. If we have kcmp() this will only return true for
         * dup()ed file descriptors, but not otherwise. If we don't
         * have kcmp() this will also return true for two fds of the same
         * file, created by separate open() calls. Since we use this
         * call mostly for filtering out duplicates in the fd store
         * this difference hopefully doesn't matter too much. */

        if (a == b)
                return true;

        /* Try to use kcmp() if we have it. */
        pid = getpid_cached();
        r = kcmp(pid, pid, KCMP_FILE, a, b);
        if (r == 0)
                return true;
        if (r > 0)
                return false;
        if (!IN_SET(errno, ENOSYS, EACCES, EPERM))
                return -errno;

        /* We don't have kcmp(), use fstat() instead. */
        if (fstat(a, &sta) < 0)
                return -errno;

        if (fstat(b, &stb) < 0)
                return -errno;

        if ((sta.st_mode & S_IFMT) != (stb.st_mode & S_IFMT))
                return false;

        /* We consider all device fds different, since two device fds
         * might refer to quite different device contexts even though
         * they share the same inode and backing dev_t. */

        if (S_ISCHR(sta.st_mode) || S_ISBLK(sta.st_mode))
                return false;

        if (sta.st_dev != stb.st_dev || sta.st_ino != stb.st_ino)
                return false;

        /* The fds refer to the same inode on disk, let's also check
         * if they have the same fd flags. This is useful to
         * distinguish the read and write side of a pipe created with
         * pipe(). */
        fa = fcntl(a, F_GETFL);
        if (fa < 0)
                return -errno;

        fb = fcntl(b, F_GETFL);
        if (fb < 0)
                return -errno;

        return fa == fb;
}