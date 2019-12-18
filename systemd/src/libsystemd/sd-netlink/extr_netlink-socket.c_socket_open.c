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
 int /*<<< orphan*/  PF_NETLINK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int SOCK_RAW ; 
 int errno ; 
 int fd_move_above_stdio (int) ; 
 int socket (int /*<<< orphan*/ ,int,int) ; 

int socket_open(int family) {
        int fd;

        fd = socket(PF_NETLINK, SOCK_RAW|SOCK_CLOEXEC|SOCK_NONBLOCK, family);
        if (fd < 0)
                return -errno;

        return fd_move_above_stdio(fd);
}