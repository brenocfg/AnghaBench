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
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  AF_NETLINK ; 
 int EINVAL ; 
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 int /*<<< orphan*/  SOCK_SEQPACKET ; 
 int /*<<< orphan*/  assert (int*) ; 
 scalar_t__ sd_is_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sd_listen_fds (int) ; 

__attribute__((used)) static int listen_fds(int *ret_ctrl, int *ret_netlink) {
        int ctrl_fd = -1, netlink_fd = -1;
        int fd, n;

        assert(ret_ctrl);
        assert(ret_netlink);

        n = sd_listen_fds(true);
        if (n < 0)
                return n;

        for (fd = SD_LISTEN_FDS_START; fd < n + SD_LISTEN_FDS_START; fd++) {
                if (sd_is_socket(fd, AF_LOCAL, SOCK_SEQPACKET, -1) > 0) {
                        if (ctrl_fd >= 0)
                                return -EINVAL;
                        ctrl_fd = fd;
                        continue;
                }

                if (sd_is_socket(fd, AF_NETLINK, SOCK_RAW, -1) > 0) {
                        if (netlink_fd >= 0)
                                return -EINVAL;
                        netlink_fd = fd;
                        continue;
                }

                return -EINVAL;
        }

        *ret_ctrl = ctrl_fd;
        *ret_netlink = netlink_fd;

        return 0;
}