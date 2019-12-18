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
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
#define  S_IFBLK 133 
#define  S_IFCHR 132 
#define  S_IFDIR 131 
#define  S_IFIFO 130 
 int S_IFMT ; 
#define  S_IFREG 129 
#define  S_IFSOCK 128 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 

const char* mode_to_inaccessible_node(mode_t mode) {
        /* This function maps a node type to a corresponding inaccessible file node. These nodes are created during
         * early boot by PID 1. In some cases we lacked the privs to create the character and block devices (maybe
         * because we run in an userns environment, or miss CAP_SYS_MKNOD, or run with a devices policy that excludes
         * device nodes with major and minor of 0), but that's fine, in that case we use an AF_UNIX file node instead,
         * which is not the same, but close enough for most uses. And most importantly, the kernel allows bind mounts
         * from socket nodes to any non-directory file nodes, and that's the most important thing that matters. */

        switch(mode & S_IFMT) {
                case S_IFREG:
                        return "/run/systemd/inaccessible/reg";

                case S_IFDIR:
                        return "/run/systemd/inaccessible/dir";

                case S_IFCHR:
                        if (access("/run/systemd/inaccessible/chr", F_OK) == 0)
                                return "/run/systemd/inaccessible/chr";
                        return "/run/systemd/inaccessible/sock";

                case S_IFBLK:
                        if (access("/run/systemd/inaccessible/blk", F_OK) == 0)
                                return "/run/systemd/inaccessible/blk";
                        return "/run/systemd/inaccessible/sock";

                case S_IFIFO:
                        return "/run/systemd/inaccessible/fifo";

                case S_IFSOCK:
                        return "/run/systemd/inaccessible/sock";
        }
        return NULL;
}