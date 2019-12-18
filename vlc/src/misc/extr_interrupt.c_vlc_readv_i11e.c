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
struct iovec {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  POLLIN ; 
 int readv (int,struct iovec*,int) ; 
 scalar_t__ vlc_poll_i11e (struct pollfd*,int,int) ; 

ssize_t vlc_readv_i11e(int fd, struct iovec *iov, int count)
{
    struct pollfd ufd;

    ufd.fd = fd;
    ufd.events = POLLIN;

    if (vlc_poll_i11e(&ufd, 1, -1) < 0)
        return -1;
    return readv(fd, iov, count);
}