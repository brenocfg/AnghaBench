#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct epoll_event {int dummy; } ;
struct TYPE_5__ {int setsize; TYPE_2__* apidata; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_6__ {int epfd; struct TYPE_6__* events; } ;
typedef  TYPE_2__ aeApiState ;

/* Variables and functions */
 int epoll_create (int) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 void* zmalloc (int) ; 

__attribute__((used)) static int aeApiCreate(aeEventLoop *eventLoop) {
    aeApiState *state = zmalloc(sizeof(aeApiState));

    if (!state) return -1;
    state->events = zmalloc(sizeof(struct epoll_event)*eventLoop->setsize);
    if (!state->events) {
        zfree(state);
        return -1;
    }
    state->epfd = epoll_create(1024); /* 1024 is just a hint for the kernel */
    if (state->epfd == -1) {
        zfree(state->events);
        zfree(state);
        return -1;
    }
    eventLoop->apidata = state;
    return 0;
}