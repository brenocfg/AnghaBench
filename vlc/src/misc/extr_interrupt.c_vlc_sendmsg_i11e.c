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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct msghdr {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLOUT ; 
 int sendmsg (int,struct msghdr const*,int) ; 
 scalar_t__ vlc_poll_i11e (struct pollfd*,int,int) ; 

ssize_t vlc_sendmsg_i11e(int fd, const struct msghdr *msg, int flags)
{
    struct pollfd ufd;

    ufd.fd = fd;
    ufd.events = POLLOUT;

    if (vlc_poll_i11e(&ufd, 1, -1) < 0)
        return -1;
    /* NOTE: MSG_EOR, MSG_OOB and MSG_NOSIGNAL should all work fine here. */
    return sendmsg(fd, msg, flags);
}