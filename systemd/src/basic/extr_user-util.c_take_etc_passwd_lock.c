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
struct flock {int /*<<< orphan*/  l_len; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; int /*<<< orphan*/  l_type; } ;

/* Variables and functions */
 char* ETC_PASSWD_LOCK_PATH ; 
 int /*<<< orphan*/  F_SETLKW ; 
 int /*<<< orphan*/  F_WRLCK ; 
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_NOCTTY ; 
 int O_NOFOLLOW ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ,struct flock*) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,char const*) ; 
 int open (char const*,int,int) ; 
 char* prefix_roota (char const*,char*) ; 
 int /*<<< orphan*/  safe_close (int) ; 

int take_etc_passwd_lock(const char *root) {

        struct flock flock = {
                .l_type = F_WRLCK,
                .l_whence = SEEK_SET,
                .l_start = 0,
                .l_len = 0,
        };

        const char *path;
        int fd, r;

        /* This is roughly the same as lckpwdf(), but not as awful. We
         * don't want to use alarm() and signals, hence we implement
         * our own trivial version of this.
         *
         * Note that shadow-utils also takes per-database locks in
         * addition to lckpwdf(). However, we don't given that they
         * are redundant as they invoke lckpwdf() first and keep
         * it during everything they do. The per-database locks are
         * awfully racy, and thus we just won't do them. */

        if (root)
                path = prefix_roota(root, ETC_PASSWD_LOCK_PATH);
        else
                path = ETC_PASSWD_LOCK_PATH;

        fd = open(path, O_WRONLY|O_CREAT|O_CLOEXEC|O_NOCTTY|O_NOFOLLOW, 0600);
        if (fd < 0)
                return log_debug_errno(errno, "Cannot open %s: %m", path);

        r = fcntl(fd, F_SETLKW, &flock);
        if (r < 0) {
                safe_close(fd);
                return log_debug_errno(errno, "Locking %s failed: %m", path);
        }

        return fd;
}