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
struct TYPE_2__ {void* ptr; } ;
struct epoll_event {int events; TYPE_1__ data; } ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int /*<<< orphan*/  EPOLL_CTL_MOD ; 
 int /*<<< orphan*/  epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 

__attribute__((used)) static void 
sp_write(int efd, int sock, void *ud, bool enable) {
	struct epoll_event ev;
	ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);
	ev.data.ptr = ud;
	epoll_ctl(efd, EPOLL_CTL_MOD, sock, &ev);
}