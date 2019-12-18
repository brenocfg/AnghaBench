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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  LOG_WARNING ; 
 int /*<<< orphan*/  assert_return (int*,int /*<<< orphan*/ ) ; 
 int log_full_errno (int /*<<< orphan*/ ,int,char*) ; 
 int socket_ioctl_fd () ; 

__attribute__((used)) static int ethtool_connect_or_warn(int *ret, bool warn) {
        int fd;

        assert_return(ret, -EINVAL);

        fd = socket_ioctl_fd();
        if (fd < 0)
                return log_full_errno(warn ? LOG_WARNING: LOG_DEBUG, fd,
                                       "ethtool: could not create control socket: %m");

        *ret = fd;

        return 0;
}