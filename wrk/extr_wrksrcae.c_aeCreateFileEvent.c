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
typedef  int /*<<< orphan*/  aeFileProc ;
struct TYPE_5__ {int mask; void* clientData; int /*<<< orphan*/ * wfileProc; int /*<<< orphan*/ * rfileProc; } ;
typedef  TYPE_1__ aeFileEvent ;
struct TYPE_6__ {int setsize; int maxfd; TYPE_1__* events; } ;
typedef  TYPE_2__ aeEventLoop ;

/* Variables and functions */
 int AE_ERR ; 
 int AE_OK ; 
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int /*<<< orphan*/  ERANGE ; 
 int aeApiAddEvent (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  errno ; 

int aeCreateFileEvent(aeEventLoop *eventLoop, int fd, int mask,
        aeFileProc *proc, void *clientData)
{
    if (fd >= eventLoop->setsize) {
        errno = ERANGE;
        return AE_ERR;
    }
    aeFileEvent *fe = &eventLoop->events[fd];

    if (aeApiAddEvent(eventLoop, fd, mask) == -1)
        return AE_ERR;
    fe->mask |= mask;
    if (mask & AE_READABLE) fe->rfileProc = proc;
    if (mask & AE_WRITABLE) fe->wfileProc = proc;
    fe->clientData = clientData;
    if (fd > eventLoop->maxfd)
        eventLoop->maxfd = fd;
    return AE_OK;
}