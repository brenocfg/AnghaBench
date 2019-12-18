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
struct TYPE_2__ {int /*<<< orphan*/  ptr; } ;
struct epoll_event {int events; TYPE_1__ data; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  strm_stream ;
typedef  int /*<<< orphan*/  strm_callback ;

/* Variables and functions */
 int EPOLLIN ; 
 int EPOLLONESHOT ; 
 int /*<<< orphan*/  EPOLL_CTL_ADD ; 
 int epoll_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct epoll_event*) ; 
 int /*<<< orphan*/  epoll_fd ; 
 int /*<<< orphan*/  io_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
io_push(int fd, strm_stream* strm, strm_callback cb)
{
  struct epoll_event ev = { 0 };

  ev.events = EPOLLIN | EPOLLONESHOT;
  ev.data.ptr = io_task(strm, cb);
  return epoll_ctl(epoll_fd, EPOLL_CTL_ADD, fd, &ev);
}