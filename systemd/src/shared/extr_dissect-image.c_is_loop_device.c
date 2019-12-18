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
struct stat {int /*<<< orphan*/  st_dev; int /*<<< orphan*/  st_mode; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOTBLK ; 
 int /*<<< orphan*/  F_OK ; 
 int SYS_BLOCK_PATH_MAX (char*) ; 
 int /*<<< orphan*/  S_ISBLK (int /*<<< orphan*/ ) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int errno ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  xsprintf_sys_block_path (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int is_loop_device(const char *path) {
        char s[SYS_BLOCK_PATH_MAX("/../loop/")];
        struct stat st;

        assert(path);

        if (stat(path, &st) < 0)
                return -errno;

        if (!S_ISBLK(st.st_mode))
                return -ENOTBLK;

        xsprintf_sys_block_path(s, "/loop/", st.st_dev);
        if (access(s, F_OK) < 0) {
                if (errno != ENOENT)
                        return -errno;

                /* The device itself isn't a loop device, but maybe it's a partition and its parent is? */
                xsprintf_sys_block_path(s, "/../loop/", st.st_dev);
                if (access(s, F_OK) < 0)
                        return errno == ENOENT ? false : -errno;
        }

        return true;
}