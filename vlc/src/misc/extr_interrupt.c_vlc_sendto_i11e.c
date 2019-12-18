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
struct sockaddr {int dummy; } ;
struct msghdr {int msg_iovlen; struct iovec* msg_iov; int /*<<< orphan*/  msg_namelen; struct sockaddr* msg_name; } ;
struct iovec {void* iov_base; size_t iov_len; } ;
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_sendmsg_i11e (int,struct msghdr*,int) ; 

ssize_t vlc_sendto_i11e(int fd, const void *buf, size_t len, int flags,
                      const struct sockaddr *addr, socklen_t addrlen)
{
    struct iovec iov = { .iov_base = (void *)buf, .iov_len = len };
    struct msghdr msg = {
        .msg_name = (struct sockaddr *)addr,
        .msg_namelen = addrlen,
        .msg_iov = &iov,
        .msg_iovlen = 1,
    };

    return vlc_sendmsg_i11e(fd, &msg, flags);
}