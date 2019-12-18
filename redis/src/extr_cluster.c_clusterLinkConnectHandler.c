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
typedef  scalar_t__ mstime_t ;
typedef  int /*<<< orphan*/  connection ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  cport; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; scalar_t__ ping_sent; } ;
typedef  TYPE_1__ clusterNode ;
struct TYPE_7__ {TYPE_1__* node; } ;
typedef  TYPE_2__ clusterLink ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTERMSG_TYPE_MEET ; 
 int /*<<< orphan*/  CLUSTERMSG_TYPE_PING ; 
 int CLUSTER_NODE_MEET ; 
 scalar_t__ CONN_STATE_CONNECTED ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 int /*<<< orphan*/  clusterReadHandler ; 
 int /*<<< orphan*/  clusterSendPing (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connGetLastError (int /*<<< orphan*/ *) ; 
 TYPE_2__* connGetPrivateData (int /*<<< orphan*/ *) ; 
 scalar_t__ connGetState (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connSetReadHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeClusterLink (TYPE_2__*) ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 

void clusterLinkConnectHandler(connection *conn) {
    clusterLink *link = connGetPrivateData(conn);
    clusterNode *node = link->node;

    /* Check if connection succeeded */
    if (connGetState(conn) != CONN_STATE_CONNECTED) {
        serverLog(LL_VERBOSE, "Connection with Node %.40s at %s:%d failed: %s",
                node->name, node->ip, node->cport,
                connGetLastError(conn));
        freeClusterLink(link);
        return;
    }

    /* Register a read handler from now on */
    connSetReadHandler(conn, clusterReadHandler);

    /* Queue a PING in the new connection ASAP: this is crucial
     * to avoid false positives in failure detection.
     *
     * If the node is flagged as MEET, we send a MEET message instead
     * of a PING one, to force the receiver to add us in its node
     * table. */
    mstime_t old_ping_sent = node->ping_sent;
    clusterSendPing(link, node->flags & CLUSTER_NODE_MEET ?
            CLUSTERMSG_TYPE_MEET : CLUSTERMSG_TYPE_PING);
    if (old_ping_sent) {
        /* If there was an active ping before the link was
         * disconnected, we want to restore the ping time, otherwise
         * replaced by the clusterSendPing() call. */
        node->ping_sent = old_ping_sent;
    }
    /* We can clear the flag after the first packet is sent.
     * If we'll never receive a PONG, we'll never send new packets
     * to this node. Instead after the PONG is received and we
     * are no longer in meet/handshake status, we want to send
     * normal PING packets. */
    node->flags &= ~CLUSTER_NODE_MEET;

    serverLog(LL_DEBUG,"Connecting with Node %.40s at %s:%d",
            node->name, node->ip, node->cport);
}