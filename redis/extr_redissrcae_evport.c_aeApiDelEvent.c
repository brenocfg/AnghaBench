#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* events; TYPE_3__* apidata; } ;
typedef  TYPE_2__ aeEventLoop ;
struct TYPE_8__ {int* pending_masks; int* pending_fds; int /*<<< orphan*/  portfd; } ;
typedef  TYPE_3__ aeApiState ;
struct TYPE_6__ {int mask; } ;

/* Variables and functions */
 int AE_NONE ; 
 int /*<<< orphan*/  PORT_SOURCE_FD ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ aeApiAssociate (char*,int /*<<< orphan*/ ,int,int) ; 
 int aeApiLookupPending (TYPE_3__*,int) ; 
 scalar_t__ evport_debug ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 scalar_t__ port_dissociate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void aeApiDelEvent(aeEventLoop *eventLoop, int fd, int mask) {
    aeApiState *state = eventLoop->apidata;
    int fullmask, pfd;

    if (evport_debug)
        fprintf(stderr, "del fd %d mask 0x%x\n", fd, mask);

    pfd = aeApiLookupPending(state, fd);

    if (pfd != -1) {
        if (evport_debug)
            fprintf(stderr, "deleting event from pending fd %d\n", fd);

        /*
         * This fd was just returned from aeApiPoll, so it's not currently
         * associated with the port.  All we need to do is update
         * pending_mask appropriately.
         */
        state->pending_masks[pfd] &= ~mask;

        if (state->pending_masks[pfd] == AE_NONE)
            state->pending_fds[pfd] = -1;

        return;
    }

    /*
     * The fd is currently associated with the port.  Like with the add case
     * above, we must look at the full mask for the file descriptor before
     * updating that association.  We don't have a good way of knowing what the
     * events are without looking into the eventLoop state directly.  We rely on
     * the fact that our caller has already updated the mask in the eventLoop.
     */

    fullmask = eventLoop->events[fd].mask;
    if (fullmask == AE_NONE) {
        /*
         * We're removing *all* events, so use port_dissociate to remove the
         * association completely.  Failure here indicates a bug.
         */
        if (evport_debug)
            fprintf(stderr, "aeApiDelEvent: port_dissociate(%d)\n", fd);

        if (port_dissociate(state->portfd, PORT_SOURCE_FD, fd) != 0) {
            perror("aeApiDelEvent: port_dissociate");
            abort(); /* will not return */
        }
    } else if (aeApiAssociate("aeApiDelEvent", state->portfd, fd,
        fullmask) != 0) {
        /*
         * ENOMEM is a potentially transient condition, but the kernel won't
         * generally return it unless things are really bad.  EAGAIN indicates
         * we've reached an resource limit, for which it doesn't make sense to
         * retry (counter-intuitively).  All other errors indicate a bug.  In any
         * of these cases, the best we can do is to abort.
         */
        abort(); /* will not return */
    }
}