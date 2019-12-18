#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_18__ {int /*<<< orphan*/  keys; } ;
struct TYPE_19__ {int flags; scalar_t__ replstate; int repldbfd; int /*<<< orphan*/ * peerid; struct TYPE_19__* argv; scalar_t__ name; int /*<<< orphan*/ * replpreamble; int /*<<< orphan*/  reply; int /*<<< orphan*/  pubsub_patterns; int /*<<< orphan*/  pubsub_channels; int /*<<< orphan*/  watched_keys; TYPE_1__ bpop; int /*<<< orphan*/ * querybuf; int /*<<< orphan*/ * pending_querybuf; scalar_t__ conn; } ;
typedef  TYPE_2__ client ;
struct TYPE_20__ {int /*<<< orphan*/ * clients_to_close; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  repl_no_slaves_since; int /*<<< orphan*/ * slaves; int /*<<< orphan*/ * monitors; scalar_t__ master; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_CLOSE_AFTER_REPLY ; 
 int CLIENT_CLOSE_ASAP ; 
 int CLIENT_MASTER ; 
 int CLIENT_MONITOR ; 
 int CLIENT_PROTECTED ; 
 int CLIENT_SLAVE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_CLIENT_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_REPLICA_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_CLIENT_CHANGE_DISCONNECTED ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_REPLICA_CHANGE_OFFLINE ; 
 scalar_t__ SLAVE_STATE_ONLINE ; 
 scalar_t__ SLAVE_STATE_SEND_BULK ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  decrRefCount (scalar_t__) ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClientArgv (TYPE_2__*) ; 
 int /*<<< orphan*/  freeClientAsync (TYPE_2__*) ; 
 int /*<<< orphan*/  freeClientMultiState (TYPE_2__*) ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ listLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pubsubUnsubscribeAllChannels (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pubsubUnsubscribeAllPatterns (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  refreshGoodSlavesCount () ; 
 int /*<<< orphan*/  replicationCacheMaster (TYPE_2__*) ; 
 int /*<<< orphan*/  replicationGetSlaveName (TYPE_2__*) ; 
 int /*<<< orphan*/  replicationHandleMasterDisconnection () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 TYPE_7__ server ; 
 int /*<<< orphan*/  serverAssert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  unblockClient (TYPE_2__*) ; 
 int /*<<< orphan*/  unlinkClient (TYPE_2__*) ; 
 int /*<<< orphan*/  unwatchAllKeys (TYPE_2__*) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void freeClient(client *c) {
    listNode *ln;

    /* If a client is protected, yet we need to free it right now, make sure
     * to at least use asynchronous freeing. */
    if (c->flags & CLIENT_PROTECTED) {
        freeClientAsync(c);
        return;
    }

    /* For connected clients, call the disconnection event of modules hooks. */
    if (c->conn) {
        moduleFireServerEvent(REDISMODULE_EVENT_CLIENT_CHANGE,
                              REDISMODULE_SUBEVENT_CLIENT_CHANGE_DISCONNECTED,
                              c);
    }

    /* If it is our master that's beging disconnected we should make sure
     * to cache the state to try a partial resynchronization later.
     *
     * Note that before doing this we make sure that the client is not in
     * some unexpected state, by checking its flags. */
    if (server.master && c->flags & CLIENT_MASTER) {
        serverLog(LL_WARNING,"Connection with master lost.");
        if (!(c->flags & (CLIENT_CLOSE_AFTER_REPLY|
                          CLIENT_CLOSE_ASAP|
                          CLIENT_BLOCKED)))
        {
            replicationCacheMaster(c);
            return;
        }
    }

    /* Log link disconnection with slave */
    if ((c->flags & CLIENT_SLAVE) && !(c->flags & CLIENT_MONITOR)) {
        serverLog(LL_WARNING,"Connection with replica %s lost.",
            replicationGetSlaveName(c));
    }

    /* Free the query buffer */
    sdsfree(c->querybuf);
    sdsfree(c->pending_querybuf);
    c->querybuf = NULL;

    /* Deallocate structures used to block on blocking ops. */
    if (c->flags & CLIENT_BLOCKED) unblockClient(c);
    dictRelease(c->bpop.keys);

    /* UNWATCH all the keys */
    unwatchAllKeys(c);
    listRelease(c->watched_keys);

    /* Unsubscribe from all the pubsub channels */
    pubsubUnsubscribeAllChannels(c,0);
    pubsubUnsubscribeAllPatterns(c,0);
    dictRelease(c->pubsub_channels);
    listRelease(c->pubsub_patterns);

    /* Free data structures. */
    listRelease(c->reply);
    freeClientArgv(c);

    /* Unlink the client: this will close the socket, remove the I/O
     * handlers, and remove references of the client from different
     * places where active clients may be referenced. */
    unlinkClient(c);

    /* Master/slave cleanup Case 1:
     * we lost the connection with a slave. */
    if (c->flags & CLIENT_SLAVE) {
        if (c->replstate == SLAVE_STATE_SEND_BULK) {
            if (c->repldbfd != -1) close(c->repldbfd);
            if (c->replpreamble) sdsfree(c->replpreamble);
        }
        list *l = (c->flags & CLIENT_MONITOR) ? server.monitors : server.slaves;
        ln = listSearchKey(l,c);
        serverAssert(ln != NULL);
        listDelNode(l,ln);
        /* We need to remember the time when we started to have zero
         * attached slaves, as after some time we'll free the replication
         * backlog. */
        if (c->flags & CLIENT_SLAVE && listLength(server.slaves) == 0)
            server.repl_no_slaves_since = server.unixtime;
        refreshGoodSlavesCount();
        /* Fire the replica change modules event. */
        if (c->replstate == SLAVE_STATE_ONLINE)
            moduleFireServerEvent(REDISMODULE_EVENT_REPLICA_CHANGE,
                                  REDISMODULE_SUBEVENT_REPLICA_CHANGE_OFFLINE,
                                  NULL);
    }

    /* Master/slave cleanup Case 2:
     * we lost the connection with the master. */
    if (c->flags & CLIENT_MASTER) replicationHandleMasterDisconnection();

    /* If this client was scheduled for async freeing we need to remove it
     * from the queue. */
    if (c->flags & CLIENT_CLOSE_ASAP) {
        ln = listSearchKey(server.clients_to_close,c);
        serverAssert(ln != NULL);
        listDelNode(server.clients_to_close,ln);
    }

    /* Release other dynamically allocated client structure fields,
     * and finally release the client structure itself. */
    if (c->name) decrRefCount(c->name);
    zfree(c->argv);
    freeClientMultiState(c);
    sdsfree(c->peerid);
    zfree(c);
}