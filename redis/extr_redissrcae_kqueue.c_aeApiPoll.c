#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct timespec {int tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct kevent {scalar_t__ filter; int /*<<< orphan*/  ident; } ;
struct TYPE_6__ {TYPE_1__* fired; int /*<<< orphan*/  setsize; TYPE_3__* apidata; } ;
typedef  TYPE_2__ aeEventLoop ;
struct TYPE_7__ {struct kevent* events; int /*<<< orphan*/  kqfd; } ;
typedef  TYPE_3__ aeApiState ;
struct TYPE_5__ {int mask; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 scalar_t__ EVFILT_READ ; 
 scalar_t__ EVFILT_WRITE ; 
 int kevent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct kevent*,int /*<<< orphan*/ ,struct timespec*) ; 

__attribute__((used)) static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
    aeApiState *state = eventLoop->apidata;
    int retval, numevents = 0;

    if (tvp != NULL) {
        struct timespec timeout;
        timeout.tv_sec = tvp->tv_sec;
        timeout.tv_nsec = tvp->tv_usec * 1000;
        retval = kevent(state->kqfd, NULL, 0, state->events, eventLoop->setsize,
                        &timeout);
    } else {
        retval = kevent(state->kqfd, NULL, 0, state->events, eventLoop->setsize,
                        NULL);
    }

    if (retval > 0) {
        int j;

        numevents = retval;
        for(j = 0; j < numevents; j++) {
            int mask = 0;
            struct kevent *e = state->events+j;

            if (e->filter == EVFILT_READ) mask |= AE_READABLE;
            if (e->filter == EVFILT_WRITE) mask |= AE_WRITABLE;
            eventLoop->fired[j].fd = e->ident;
            eventLoop->fired[j].mask = mask;
        }
    }
    return numevents;
}