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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_6__ {scalar_t__ replstate; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ client ;
struct TYPE_7__ {int /*<<< orphan*/  el; int /*<<< orphan*/  slaves; } ;

/* Variables and functions */
 int AE_WRITABLE ; 
 scalar_t__ SLAVE_STATE_ONLINE ; 
 int aeGetFileEvents (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ clientHasPendingReplies (TYPE_1__*) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  writeToClient (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

void flushSlavesOutputBuffers(void) {
    listIter li;
    listNode *ln;

    listRewind(server.slaves,&li);
    while((ln = listNext(&li))) {
        client *slave = listNodeValue(ln);
        int events;

        /* Note that the following will not flush output buffers of slaves
         * in STATE_ONLINE but having put_online_on_ack set to true: in this
         * case the writable event is never installed, since the purpose
         * of put_online_on_ack is to postpone the moment it is installed.
         * This is what we want since slaves in this state should not receive
         * writes before the first ACK. */
        events = aeGetFileEvents(server.el,slave->fd);
        if (events & AE_WRITABLE &&
            slave->replstate == SLAVE_STATE_ONLINE &&
            clientHasPendingReplies(slave))
        {
            writeToClient(slave->fd,slave,0);
        }
    }
}