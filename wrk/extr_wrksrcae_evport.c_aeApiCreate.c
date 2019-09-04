#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* apidata; } ;
typedef  TYPE_1__ aeEventLoop ;
struct TYPE_7__ {int portfd; int* pending_fds; int /*<<< orphan*/ * pending_masks; scalar_t__ npending; } ;
typedef  TYPE_2__ aeApiState ;

/* Variables and functions */
 int /*<<< orphan*/  AE_NONE ; 
 int MAX_EVENT_BATCHSZ ; 
 int port_create () ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 
 TYPE_2__* zmalloc (int) ; 

__attribute__((used)) static int aeApiCreate(aeEventLoop *eventLoop) {
    int i;
    aeApiState *state = zmalloc(sizeof(aeApiState));
    if (!state) return -1;

    state->portfd = port_create();
    if (state->portfd == -1) {
        zfree(state);
        return -1;
    }

    state->npending = 0;

    for (i = 0; i < MAX_EVENT_BATCHSZ; i++) {
        state->pending_fds[i] = -1;
        state->pending_masks[i] = AE_NONE;
    }

    eventLoop->apidata = state;
    return 0;
}