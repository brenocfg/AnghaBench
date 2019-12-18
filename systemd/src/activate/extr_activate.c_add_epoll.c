#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int fd; } ;
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  errno ; 
 int log_error_errno (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static int add_epoll(int epoll_fd, int fd) {
        struct epoll_event ev = {
                .events = EPOLLIN,
                .data.fd = fd,
        };

        assert(epoll_fd >= 0);
        assert(fd >= 0);

        if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev) < 0)
                return log_error_errno(errno, "Failed to add event on epoll fd:%d for fd:%d: %m", epoll_fd, fd);

        return 0;
}