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
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int AT_FDCWD ; 
 scalar_t__ EPERM ; 
 int O_NOATIME ; 
 int O_NOFOLLOW ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_debug_errno (scalar_t__,char*,char*,char const*) ; 
 int /*<<< orphan*/ * xopendirat (int,char const*,int) ; 

__attribute__((used)) static DIR* xopendirat_nomod(int dirfd, const char *path) {
        DIR *dir;

        dir = xopendirat(dirfd, path, O_NOFOLLOW|O_NOATIME);
        if (dir)
                return dir;

        log_debug_errno(errno, "Cannot open %sdirectory \"%s\": %m", dirfd == AT_FDCWD ? "" : "sub", path);
        if (errno != EPERM)
                return NULL;

        dir = xopendirat(dirfd, path, O_NOFOLLOW);
        if (!dir)
                log_debug_errno(errno, "Cannot open %sdirectory \"%s\": %m", dirfd == AT_FDCWD ? "" : "sub", path);

        return dir;
}