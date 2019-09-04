#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int mstime_t ;
struct TYPE_9__ {int timeout; } ;
struct TYPE_10__ {int flags; scalar_t__ lastinteraction; TYPE_1__ bpop; } ;
typedef  TYPE_2__ client ;
struct TYPE_11__ {scalar_t__ maxidletime; scalar_t__ cluster_enabled; } ;

/* Variables and functions */
 int CLIENT_BLOCKED ; 
 int CLIENT_MASTER ; 
 int CLIENT_PUBSUB ; 
 int CLIENT_SLAVE ; 
 int /*<<< orphan*/  LL_VERBOSE ; 
 scalar_t__ clusterRedirectBlockedClientIfNeeded (TYPE_2__*) ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 int /*<<< orphan*/  replyToBlockedClientTimedOut (TYPE_2__*) ; 
 TYPE_4__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unblockClient (TYPE_2__*) ; 

int clientsCronHandleTimeout(client *c, mstime_t now_ms) {
    time_t now = now_ms/1000;

    if (server.maxidletime &&
        !(c->flags & CLIENT_SLAVE) &&    /* no timeout for slaves */
        !(c->flags & CLIENT_MASTER) &&   /* no timeout for masters */
        !(c->flags & CLIENT_BLOCKED) &&  /* no timeout for BLPOP */
        !(c->flags & CLIENT_PUBSUB) &&   /* no timeout for Pub/Sub clients */
        (now - c->lastinteraction > server.maxidletime))
    {
        serverLog(LL_VERBOSE,"Closing idle client");
        freeClient(c);
        return 1;
    } else if (c->flags & CLIENT_BLOCKED) {
        /* Blocked OPS timeout is handled with milliseconds resolution.
         * However note that the actual resolution is limited by
         * server.hz. */

        if (c->bpop.timeout != 0 && c->bpop.timeout < now_ms) {
            /* Handle blocking operation specific timeout. */
            replyToBlockedClientTimedOut(c);
            unblockClient(c);
        } else if (server.cluster_enabled) {
            /* Cluster: handle unblock & redirect of clients blocked
             * into keys no longer served by this server. */
            if (clusterRedirectBlockedClientIfNeeded(c))
                unblockClient(c);
        }
    }
    return 0;
}