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
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int accept (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 

int vlc_accept (int lfd, struct sockaddr *addr, socklen_t *alen, bool nonblock)
{
    do
    {
        int fd = accept (lfd, addr, alen);
        if (fd != -1)
        {
            fcntl (fd, F_SETFD, FD_CLOEXEC);
            if (nonblock)
                fcntl (fd, F_SETFL, fcntl (fd, F_GETFL, 0) | O_NONBLOCK);
            return fd;
        }
    }
    while (errno == EINTR);

    return -1;
}