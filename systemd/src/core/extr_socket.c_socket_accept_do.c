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
typedef  int /*<<< orphan*/  Socket ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ ERRNO_IS_ACCEPT_AGAIN (int) ; 
 int SOCK_CLOEXEC ; 
 int SOCK_NONBLOCK ; 
 int accept4 (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 

__attribute__((used)) static int socket_accept_do(Socket *s, int fd) {
        int cfd;

        assert(s);
        assert(fd >= 0);

        cfd = accept4(fd, NULL, NULL, SOCK_NONBLOCK|SOCK_CLOEXEC);
        if (cfd < 0)
                /* Convert transient network errors into clean and well-defined EAGAIN */
                return ERRNO_IS_ACCEPT_AGAIN(errno) ? -EAGAIN : -errno;

        return cfd;
}