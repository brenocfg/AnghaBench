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
 int /*<<< orphan*/  AF_NETLINK ; 
 int EINVAL ; 
 int SD_LISTEN_FDS_START ; 
 int /*<<< orphan*/  SOCK_RAW ; 
 scalar_t__ sd_is_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int sd_listen_fds (int) ; 

__attribute__((used)) static int systemd_netlink_fd(void) {
        int n, fd, rtnl_fd = -EINVAL;

        n = sd_listen_fds(true);
        if (n <= 0)
                return -EINVAL;

        for (fd = SD_LISTEN_FDS_START; fd < SD_LISTEN_FDS_START + n; fd ++) {
                if (sd_is_socket(fd, AF_NETLINK, SOCK_RAW, -1) > 0) {
                        if (rtnl_fd >= 0)
                                return -EINVAL;

                        rtnl_fd = fd;
                }
        }

        return rtnl_fd;
}