#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_sec; int tv_usec; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
struct epoll_event {int events; TYPE_1__ data; } ;
struct TYPE_8__ {TYPE_2__* fired; int /*<<< orphan*/  setsize; TYPE_4__* apidata; } ;
typedef  TYPE_3__ aeEventLoop ;
struct TYPE_9__ {struct epoll_event* events; int /*<<< orphan*/  epfd; } ;
typedef  TYPE_4__ aeApiState ;
struct TYPE_7__ {int mask; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int EPOLLERR ; 
 int EPOLLHUP ; 
 int EPOLLIN ; 
 int EPOLLOUT ; 
 int epoll_wait (int /*<<< orphan*/ ,struct epoll_event*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
    aeApiState *state = eventLoop->apidata;
    int retval, numevents = 0;

    retval = epoll_wait(state->epfd,state->events,eventLoop->setsize,
            tvp ? (tvp->tv_sec*1000 + tvp->tv_usec/1000) : -1);
    if (retval > 0) {
        int j;

        numevents = retval;
        for (j = 0; j < numevents; j++) {
            int mask = 0;
            struct epoll_event *e = state->events+j;

            if (e->events & EPOLLIN) mask |= AE_READABLE;
            if (e->events & EPOLLOUT) mask |= AE_WRITABLE;
            if (e->events & EPOLLERR) mask |= AE_WRITABLE|AE_READABLE;
            if (e->events & EPOLLHUP) mask |= AE_WRITABLE|AE_READABLE;
            eventLoop->fired[j].fd = e->data.fd;
            eventLoop->fired[j].mask = mask;
        }
    }
    return numevents;
}