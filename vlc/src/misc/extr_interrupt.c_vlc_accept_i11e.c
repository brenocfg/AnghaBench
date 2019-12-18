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
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int vlc_accept (int,struct sockaddr*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ vlc_poll_i11e (struct pollfd*,int,int) ; 

int vlc_accept_i11e(int fd, struct sockaddr *addr, socklen_t *addrlen,
                  bool blocking)
{
    struct pollfd ufd;

    ufd.fd = fd;
    ufd.events = POLLIN;

    if (vlc_poll_i11e(&ufd, 1, -1) < 0)
        return -1;

    return vlc_accept(fd, addr, addrlen, blocking);
}