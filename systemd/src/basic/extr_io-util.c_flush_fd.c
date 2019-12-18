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
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int LINE_MAX ; 
 int /*<<< orphan*/  POLLIN ; 
 int errno ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,int) ; 

int flush_fd(int fd) {
        struct pollfd pollfd = {
                .fd = fd,
                .events = POLLIN,
        };
        int count = 0;

        /* Read from the specified file descriptor, until POLLIN is not set anymore, throwing away everything
         * read. Note that some file descriptors (notable IP sockets) will trigger POLLIN even when no data can be read
         * (due to IP packet checksum mismatches), hence this function is only safe to be non-blocking if the fd used
         * was set to non-blocking too. */

        for (;;) {
                char buf[LINE_MAX];
                ssize_t l;
                int r;

                r = poll(&pollfd, 1, 0);
                if (r < 0) {
                        if (errno == EINTR)
                                continue;

                        return -errno;

                } else if (r == 0)
                        return count;

                l = read(fd, buf, sizeof(buf));
                if (l < 0) {

                        if (errno == EINTR)
                                continue;

                        if (errno == EAGAIN)
                                return count;

                        return -errno;
                } else if (l == 0)
                        return count;

                count += (int) l;
        }
}