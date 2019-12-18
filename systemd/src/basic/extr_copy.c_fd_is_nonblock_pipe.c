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
 int FD_IS_BLOCKING_PIPE ; 
 int FD_IS_NONBLOCKING_PIPE ; 
 int FD_IS_NO_PIPE ; 
 scalar_t__ FLAGS_SET (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  S_ISFIFO (int /*<<< orphan*/ ) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 scalar_t__ fstat (int,struct stat*) ; 

__attribute__((used)) static int fd_is_nonblock_pipe(int fd) {
        struct stat st;
        int flags;

        /* Checks whether the specified file descriptor refers to a pipe, and if so if O_NONBLOCK is set. */

        if (fstat(fd, &st) < 0)
                return -errno;

        if (!S_ISFIFO(st.st_mode))
                return FD_IS_NO_PIPE;

        flags = fcntl(fd, F_GETFL);
        if (flags < 0)
                return -errno;

        return FLAGS_SET(flags, O_NONBLOCK) ? FD_IS_NONBLOCKING_PIPE : FD_IS_BLOCKING_PIPE;
}