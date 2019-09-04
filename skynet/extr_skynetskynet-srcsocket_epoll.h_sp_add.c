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
struct epoll_event {TYPE_1__ data; int /*<<< orphan*/  events; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int epoll_ctl (int,int /*<<< orphan*/ ,int,struct epoll_event*) ; 

__attribute__((used)) static int 
sp_add(int efd, int sock, void *ud) {
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.ptr = ud;
	if (epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev) == -1) {
		return 1;
	}
	return 0;
}