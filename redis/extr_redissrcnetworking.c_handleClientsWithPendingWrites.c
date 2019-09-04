#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ client ;
struct TYPE_9__ {scalar_t__ aof_state; scalar_t__ aof_fsync; int /*<<< orphan*/  el; int /*<<< orphan*/  clients_pending_write; } ;

/* Variables and functions */
 int AE_BARRIER ; 
 scalar_t__ AE_ERR ; 
 int AE_WRITABLE ; 
 scalar_t__ AOF_FSYNC_ALWAYS ; 
 scalar_t__ AOF_ON ; 
 int CLIENT_PENDING_WRITE ; 
 int CLIENT_PROTECTED ; 
 scalar_t__ C_ERR ; 
 scalar_t__ aeCreateFileEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ clientHasPendingReplies (TYPE_1__*) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_1__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listNext (int /*<<< orphan*/ *) ; 
 TYPE_1__* listNodeValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sendReplyToClient ; 
 TYPE_3__ server ; 
 scalar_t__ writeToClient (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 

int handleClientsWithPendingWrites(void) {
    listIter li;
    listNode *ln;
    int processed = listLength(server.clients_pending_write);

    listRewind(server.clients_pending_write,&li);
    while((ln = listNext(&li))) {
        client *c = listNodeValue(ln);
        c->flags &= ~CLIENT_PENDING_WRITE;
        listDelNode(server.clients_pending_write,ln);

        /* If a client is protected, don't do anything,
         * that may trigger write error or recreate handler. */
        if (c->flags & CLIENT_PROTECTED) continue;

        /* Try to write buffers to the client socket. */
        if (writeToClient(c->fd,c,0) == C_ERR) continue;

        /* If after the synchronous writes above we still have data to
         * output to the client, we need to install the writable handler. */
        if (clientHasPendingReplies(c)) {
            int ae_flags = AE_WRITABLE;
            /* For the fsync=always policy, we want that a given FD is never
             * served for reading and writing in the same event loop iteration,
             * so that in the middle of receiving the query, and serving it
             * to the client, we'll call beforeSleep() that will do the
             * actual fsync of AOF to disk. AE_BARRIER ensures that. */
            if (server.aof_state == AOF_ON &&
                server.aof_fsync == AOF_FSYNC_ALWAYS)
            {
                ae_flags |= AE_BARRIER;
            }
            if (aeCreateFileEvent(server.el, c->fd, ae_flags,
                sendReplyToClient, c) == AE_ERR)
            {
                    freeClientAsync(c);
            }
        }
    }
    return processed;
}