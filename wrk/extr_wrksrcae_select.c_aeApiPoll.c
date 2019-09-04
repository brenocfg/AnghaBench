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
struct timeval {int dummy; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_7__ {int mask; } ;
typedef  TYPE_2__ aeFileEvent ;
struct TYPE_8__ {int maxfd; TYPE_1__* fired; TYPE_2__* events; TYPE_4__* apidata; } ;
typedef  TYPE_3__ aeEventLoop ;
struct TYPE_9__ {int /*<<< orphan*/  _wfds; int /*<<< orphan*/  _rfds; int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;
typedef  TYPE_4__ aeApiState ;
struct TYPE_6__ {int fd; int mask; } ;

/* Variables and functions */
 int AE_NONE ; 
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int aeApiPoll(aeEventLoop *eventLoop, struct timeval *tvp) {
    aeApiState *state = eventLoop->apidata;
    int retval, j, numevents = 0;

    memcpy(&state->_rfds,&state->rfds,sizeof(fd_set));
    memcpy(&state->_wfds,&state->wfds,sizeof(fd_set));

    retval = select(eventLoop->maxfd+1,
                &state->_rfds,&state->_wfds,NULL,tvp);
    if (retval > 0) {
        for (j = 0; j <= eventLoop->maxfd; j++) {
            int mask = 0;
            aeFileEvent *fe = &eventLoop->events[j];

            if (fe->mask == AE_NONE) continue;
            if (fe->mask & AE_READABLE && FD_ISSET(j,&state->_rfds))
                mask |= AE_READABLE;
            if (fe->mask & AE_WRITABLE && FD_ISSET(j,&state->_wfds))
                mask |= AE_WRITABLE;
            eventLoop->fired[numevents].fd = j;
            eventLoop->fired[numevents].mask = mask;
            numevents++;
        }
    }
    return numevents;
}