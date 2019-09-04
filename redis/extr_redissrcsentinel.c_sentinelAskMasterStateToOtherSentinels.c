#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int last_master_down_reply_time; int flags; scalar_t__ failover_state; TYPE_2__* link; TYPE_1__* addr; int /*<<< orphan*/ * leader; int /*<<< orphan*/  sentinels; } ;
typedef  TYPE_3__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  port ;
typedef  int mstime_t ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_12__ {char* myid; int /*<<< orphan*/  current_epoch; } ;
struct TYPE_10__ {int /*<<< orphan*/  pending_commands; int /*<<< orphan*/  cc; scalar_t__ disconnected; } ;
struct TYPE_9__ {int /*<<< orphan*/  ip; int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int C_OK ; 
 int SENTINEL_ASK_FORCED ; 
 int SENTINEL_ASK_PERIOD ; 
 scalar_t__ SENTINEL_FAILOVER_STATE_NONE ; 
 int SRI_MASTER_DOWN ; 
 int SRI_S_DOWN ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_3__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ll2string (char*,int,int /*<<< orphan*/ ) ; 
 int mstime () ; 
 int redisAsyncCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 TYPE_6__ sentinel ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  sentinelReceiveIsMasterDownReply ; 

void sentinelAskMasterStateToOtherSentinels(sentinelRedisInstance *master, int flags) {
    dictIterator *di;
    dictEntry *de;

    di = dictGetIterator(master->sentinels);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *ri = dictGetVal(de);
        mstime_t elapsed = mstime() - ri->last_master_down_reply_time;
        char port[32];
        int retval;

        /* If the master state from other sentinel is too old, we clear it. */
        if (elapsed > SENTINEL_ASK_PERIOD*5) {
            ri->flags &= ~SRI_MASTER_DOWN;
            sdsfree(ri->leader);
            ri->leader = NULL;
        }

        /* Only ask if master is down to other sentinels if:
         *
         * 1) We believe it is down, or there is a failover in progress.
         * 2) Sentinel is connected.
         * 3) We did not receive the info within SENTINEL_ASK_PERIOD ms. */
        if ((master->flags & SRI_S_DOWN) == 0) continue;
        if (ri->link->disconnected) continue;
        if (!(flags & SENTINEL_ASK_FORCED) &&
            mstime() - ri->last_master_down_reply_time < SENTINEL_ASK_PERIOD)
            continue;

        /* Ask */
        ll2string(port,sizeof(port),master->addr->port);
        retval = redisAsyncCommand(ri->link->cc,
                    sentinelReceiveIsMasterDownReply, ri,
                    "%s is-master-down-by-addr %s %s %llu %s",
                    sentinelInstanceMapCommand(ri,"SENTINEL"),
                    master->addr->ip, port,
                    sentinel.current_epoch,
                    (master->failover_state > SENTINEL_FAILOVER_STATE_NONE) ?
                    sentinel.myid : "*");
        if (retval == C_OK) ri->link->pending_commands++;
    }
    dictReleaseIterator(di);
}