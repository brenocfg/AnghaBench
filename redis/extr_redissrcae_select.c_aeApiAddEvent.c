#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* apidata; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_5__ {int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;
typedef  TYPE_2__ aeApiState ;

/* Variables and functions */
 int AE_READABLE ; 
 int AE_WRITABLE ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int aeApiAddEvent(aeEventLoop *eventLoop, int fd, int mask) {
    aeApiState *state = eventLoop->apidata;

    if (mask & AE_READABLE) FD_SET(fd,&state->rfds);
    if (mask & AE_WRITABLE) FD_SET(fd,&state->wfds);
    return 0;
}