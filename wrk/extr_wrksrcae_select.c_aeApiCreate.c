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
struct TYPE_5__ {TYPE_2__* apidata; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_6__ {int /*<<< orphan*/  wfds; int /*<<< orphan*/  rfds; } ;
typedef  TYPE_2__ aeApiState ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 TYPE_2__* zmalloc (int) ; 

__attribute__((used)) static int aeApiCreate(aeEventLoop *eventLoop) {
    aeApiState *state = zmalloc(sizeof(aeApiState));

    if (!state) return -1;
    FD_ZERO(&state->rfds);
    FD_ZERO(&state->wfds);
    eventLoop->apidata = state;
    return 0;
}