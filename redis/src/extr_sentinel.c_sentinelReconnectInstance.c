#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_22__ {int flags; TYPE_1__* addr; TYPE_3__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
typedef  scalar_t__ mstime_t ;
struct TYPE_23__ {scalar_t__ disconnected; scalar_t__ last_reconn_time; TYPE_6__* pc; TYPE_6__* cc; void* pc_conn_time; void* cc_conn_time; scalar_t__ pending_commands; } ;
typedef  TYPE_3__ instanceLink ;
struct TYPE_25__ {TYPE_3__* data; int /*<<< orphan*/  errstr; scalar_t__ err; } ;
struct TYPE_24__ {int /*<<< orphan*/  el; scalar_t__ tls_replication; } ;
struct TYPE_21__ {scalar_t__ port; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 scalar_t__ C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_DEBUG ; 
 int /*<<< orphan*/  NET_FIRST_BIND_ADDR ; 
 int /*<<< orphan*/  SENTINEL_HELLO_CHANNEL ; 
 scalar_t__ SENTINEL_PING_PERIOD ; 
 int SRI_MASTER ; 
 int SRI_SENTINEL ; 
 int SRI_SLAVE ; 
 int /*<<< orphan*/  instanceLinkCloseConnection (TYPE_3__*,TYPE_6__*) ; 
 scalar_t__ instanceLinkNegotiateTLS (TYPE_6__*) ; 
 void* mstime () ; 
 int /*<<< orphan*/  redisAeAttach (int /*<<< orphan*/ ,TYPE_6__*) ; 
 int redisAsyncCommand (TYPE_6__*,int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* redisAsyncConnectBind (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetConnectCallback (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redisAsyncSetDisconnectCallback (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelDisconnectCallback ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sentinelLinkEstablishedCallback ; 
 int /*<<< orphan*/  sentinelReceiveHelloMessages ; 
 int /*<<< orphan*/  sentinelSendAuthIfNeeded (TYPE_2__*,TYPE_6__*) ; 
 int /*<<< orphan*/  sentinelSendPing (TYPE_2__*) ; 
 int /*<<< orphan*/  sentinelSetClientName (TYPE_2__*,TYPE_6__*,char*) ; 
 TYPE_4__ server ; 

void sentinelReconnectInstance(sentinelRedisInstance *ri) {
    if (ri->link->disconnected == 0) return;
    if (ri->addr->port == 0) return; /* port == 0 means invalid address. */
    instanceLink *link = ri->link;
    mstime_t now = mstime();

    if (now - ri->link->last_reconn_time < SENTINEL_PING_PERIOD) return;
    ri->link->last_reconn_time = now;

    /* Commands connection. */
    if (link->cc == NULL) {
        link->cc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
        if (!link->cc->err && server.tls_replication &&
                (instanceLinkNegotiateTLS(link->cc) == C_ERR)) {
            sentinelEvent(LL_DEBUG,"-cmd-link-reconnection",ri,"%@ #Failed to initialize TLS");
            instanceLinkCloseConnection(link,link->cc);
        } else if (link->cc->err) {
            sentinelEvent(LL_DEBUG,"-cmd-link-reconnection",ri,"%@ #%s",
                link->cc->errstr);
            instanceLinkCloseConnection(link,link->cc);
        } else {
            link->pending_commands = 0;
            link->cc_conn_time = mstime();
            link->cc->data = link;
            redisAeAttach(server.el,link->cc);
            redisAsyncSetConnectCallback(link->cc,
                    sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(link->cc,
                    sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,link->cc);
            sentinelSetClientName(ri,link->cc,"cmd");

            /* Send a PING ASAP when reconnecting. */
            sentinelSendPing(ri);
        }
    }
    /* Pub / Sub */
    if ((ri->flags & (SRI_MASTER|SRI_SLAVE)) && link->pc == NULL) {
        link->pc = redisAsyncConnectBind(ri->addr->ip,ri->addr->port,NET_FIRST_BIND_ADDR);
        if (!link->pc->err && server.tls_replication &&
                (instanceLinkNegotiateTLS(link->pc) == C_ERR)) {
            sentinelEvent(LL_DEBUG,"-pubsub-link-reconnection",ri,"%@ #Failed to initialize TLS");
        } else if (link->pc->err) {
            sentinelEvent(LL_DEBUG,"-pubsub-link-reconnection",ri,"%@ #%s",
                link->pc->errstr);
            instanceLinkCloseConnection(link,link->pc);
        } else {
            int retval;

            link->pc_conn_time = mstime();
            link->pc->data = link;
            redisAeAttach(server.el,link->pc);
            redisAsyncSetConnectCallback(link->pc,
                    sentinelLinkEstablishedCallback);
            redisAsyncSetDisconnectCallback(link->pc,
                    sentinelDisconnectCallback);
            sentinelSendAuthIfNeeded(ri,link->pc);
            sentinelSetClientName(ri,link->pc,"pubsub");
            /* Now we subscribe to the Sentinels "Hello" channel. */
            retval = redisAsyncCommand(link->pc,
                sentinelReceiveHelloMessages, ri, "%s %s",
                sentinelInstanceMapCommand(ri,"SUBSCRIBE"),
                SENTINEL_HELLO_CHANNEL);
            if (retval != C_OK) {
                /* If we can't subscribe, the Pub/Sub connection is useless
                 * and we can simply disconnect it and try again. */
                instanceLinkCloseConnection(link,link->pc);
                return;
            }
        }
    }
    /* Clear the disconnected status only if we have both the connections
     * (or just the commands connection if this is a sentinel instance). */
    if (link->cc && (ri->flags & SRI_SENTINEL || link->pc))
        link->disconnected = 0;
}