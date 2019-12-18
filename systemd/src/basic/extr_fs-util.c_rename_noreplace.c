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

/* Variables and functions */
 int /*<<< orphan*/  AT_SYMLINK_NOFOLLOW ; 
 int EEXIST ; 
 int /*<<< orphan*/  EINVAL ; 
 int ENOENT ; 
 int /*<<< orphan*/  ENOSYS ; 
 int /*<<< orphan*/  ENOTTY ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  F_OK ; 
 int /*<<< orphan*/  IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RENAME_NOREPLACE ; 
 int errno ; 
 scalar_t__ faccessat (int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ linkat (int,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ renameat (int,char const*,int,char const*) ; 
 scalar_t__ renameat2 (int,char const*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlinkat (int,char const*,int /*<<< orphan*/ ) ; 

int rename_noreplace(int olddirfd, const char *oldpath, int newdirfd, const char *newpath) {
        int r;

        /* Try the ideal approach first */
        if (renameat2(olddirfd, oldpath, newdirfd, newpath, RENAME_NOREPLACE) >= 0)
                return 0;

        /* renameat2() exists since Linux 3.15, btrfs and FAT added support for it later. If it is not implemented,
         * fall back to a different method. */
        if (!IN_SET(errno, EINVAL, ENOSYS, ENOTTY))
                return -errno;

        /* Let's try to use linkat()+unlinkat() as fallback. This doesn't work on directories and on some file systems
         * that do not support hard links (such as FAT, most prominently), but for files it's pretty close to what we
         * want — though not atomic (i.e. for a short period both the new and the old filename will exist). */
        if (linkat(olddirfd, oldpath, newdirfd, newpath, 0) >= 0) {

                if (unlinkat(olddirfd, oldpath, 0) < 0) {
                        r = -errno; /* Backup errno before the following unlinkat() alters it */
                        (void) unlinkat(newdirfd, newpath, 0);
                        return r;
                }

                return 0;
        }

        if (!IN_SET(errno, EINVAL, ENOSYS, ENOTTY, EPERM)) /* FAT returns EPERM on link()… */
                return -errno;

        /* OK, neither RENAME_NOREPLACE nor linkat()+unlinkat() worked. Let's then fallback to the racy TOCTOU
         * vulnerable accessat(F_OK) check followed by classic, replacing renameat(), we have nothing better. */

        if (faccessat(newdirfd, newpath, F_OK, AT_SYMLINK_NOFOLLOW) >= 0)
                return -EEXIST;
        if (errno != ENOENT)
                return -errno;

        if (renameat(olddirfd, oldpath, newdirfd, newpath) < 0)
                return -errno;

        return 0;
}