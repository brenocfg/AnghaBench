#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int flags; int /*<<< orphan*/ * peerid; scalar_t__ bufpos; scalar_t__ reply_bytes; scalar_t__ sentlen; int /*<<< orphan*/  reply; } ;
typedef  TYPE_2__ client ;
struct TYPE_10__ {TYPE_1__* master; TYPE_1__* cached_master; } ;
struct TYPE_8__ {int /*<<< orphan*/  reploff; int /*<<< orphan*/  read_reploff; int /*<<< orphan*/  pending_querybuf; int /*<<< orphan*/  querybuf; } ;

/* Variables and functions */
 int CLIENT_MULTI ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  discardTransaction (TYPE_2__*) ; 
 int /*<<< orphan*/  listEmpty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  replicationHandleMasterDisconnection () ; 
 int /*<<< orphan*/  resetClient (TYPE_2__*) ; 
 int /*<<< orphan*/  sdsclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlinkClient (TYPE_2__*) ; 

void replicationCacheMaster(client *c) {
    serverAssert(server.master != NULL && server.cached_master == NULL);
    serverLog(LL_NOTICE,"Caching the disconnected master state.");

    /* Unlink the client from the server structures. */
    unlinkClient(c);

    /* Reset the master client so that's ready to accept new commands:
     * we want to discard te non processed query buffers and non processed
     * offsets, including pending transactions, already populated arguments,
     * pending outputs to the master. */
    sdsclear(server.master->querybuf);
    sdsclear(server.master->pending_querybuf);
    server.master->read_reploff = server.master->reploff;
    if (c->flags & CLIENT_MULTI) discardTransaction(c);
    listEmpty(c->reply);
    c->sentlen = 0;
    c->reply_bytes = 0;
    c->bufpos = 0;
    resetClient(c);

    /* Save the master. Server.master will be set to null later by
     * replicationHandleMasterDisconnection(). */
    server.cached_master = server.master;

    /* Invalidate the Peer ID cache. */
    if (c->peerid) {
        sdsfree(c->peerid);
        c->peerid = NULL;
    }

    /* Caching the master happens instead of the actual freeClient() call,
     * so make sure to adjust the replication state. This function will
     * also set server.master to NULL. */
    replicationHandleMasterDisconnection();
}