#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct aeEventLoop {int dummy; } ;
typedef  int /*<<< orphan*/  robj ;
struct TYPE_2__ {int /*<<< orphan*/  unblocked_clients; int /*<<< orphan*/  clients_waiting_acks; scalar_t__ get_ack_from_slaves; int /*<<< orphan*/  slaveseldb; int /*<<< orphan*/  slaves; int /*<<< orphan*/ * masterhost; scalar_t__ active_expire_enabled; scalar_t__ cluster_enabled; int /*<<< orphan*/  el; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACTIVE_EXPIRE_CYCLE_FAST ; 
 int /*<<< orphan*/  UNUSED (struct aeEventLoop*) ; 
 int /*<<< orphan*/  activeExpireCycle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aeSetDontWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterBeforeSleep () ; 
 int /*<<< orphan*/ * createStringObject (char*,int) ; 
 int /*<<< orphan*/  decrRefCount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flushAppendOnlyFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClientsInAsyncFreeQueue () ; 
 int /*<<< orphan*/  handleClientsWithPendingWritesUsingThreads () ; 
 scalar_t__ listLength (int /*<<< orphan*/ ) ; 
 scalar_t__ moduleCount () ; 
 int /*<<< orphan*/  moduleHandleBlockedClients () ; 
 int /*<<< orphan*/  moduleReleaseGIL () ; 
 int /*<<< orphan*/  processClientsWaitingReplicas () ; 
 int /*<<< orphan*/  processUnblockedClients () ; 
 int /*<<< orphan*/  replicationFeedSlaves (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  tlsHasPendingData () ; 
 int /*<<< orphan*/  tlsProcessPendingData () ; 

void beforeSleep(struct aeEventLoop *eventLoop) {
    UNUSED(eventLoop);

    /* Handle TLS pending data. (must be done before flushAppendOnlyFile) */
    tlsProcessPendingData();
    /* If tls still has pending unread data don't sleep at all. */
    aeSetDontWait(server.el, tlsHasPendingData());

    /* Call the Redis Cluster before sleep function. Note that this function
     * may change the state of Redis Cluster (from ok to fail or vice versa),
     * so it's a good idea to call it before serving the unblocked clients
     * later in this function. */
    if (server.cluster_enabled) clusterBeforeSleep();

    /* Run a fast expire cycle (the called function will return
     * ASAP if a fast cycle is not needed). */
    if (server.active_expire_enabled && server.masterhost == NULL)
        activeExpireCycle(ACTIVE_EXPIRE_CYCLE_FAST);

    /* Send all the slaves an ACK request if at least one client blocked
     * during the previous event loop iteration. */
    if (server.get_ack_from_slaves) {
        robj *argv[3];

        argv[0] = createStringObject("REPLCONF",8);
        argv[1] = createStringObject("GETACK",6);
        argv[2] = createStringObject("*",1); /* Not used argument. */
        replicationFeedSlaves(server.slaves, server.slaveseldb, argv, 3);
        decrRefCount(argv[0]);
        decrRefCount(argv[1]);
        decrRefCount(argv[2]);
        server.get_ack_from_slaves = 0;
    }

    /* Unblock all the clients blocked for synchronous replication
     * in WAIT. */
    if (listLength(server.clients_waiting_acks))
        processClientsWaitingReplicas();

    /* Check if there are clients unblocked by modules that implement
     * blocking commands. */
    if (moduleCount()) moduleHandleBlockedClients();

    /* Try to process pending commands for clients that were just unblocked. */
    if (listLength(server.unblocked_clients))
        processUnblockedClients();

    /* Write the AOF buffer on disk */
    flushAppendOnlyFile(0);

    /* Handle writes with pending output buffers. */
    handleClientsWithPendingWritesUsingThreads();

    /* Close clients that need to be closed asynchronous */
    freeClientsInAsyncFreeQueue();

    /* Before we are going to sleep, let the threads access the dataset by
     * releasing the GIL. Redis main thread will not touch anything at this
     * time. */
    if (moduleCount()) moduleReleaseGIL();
}