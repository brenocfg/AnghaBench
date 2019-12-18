#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; scalar_t__ master_link_down_time; int down_after_period; scalar_t__ info_refresh; int last_pub_time; TYPE_2__* link; TYPE_1__* master; } ;
typedef  TYPE_3__ sentinelRedisInstance ;
typedef  int mstime_t ;
struct TYPE_10__ {int pending_commands; int refcount; int last_pong_time; int last_ping_time; int /*<<< orphan*/  cc; scalar_t__ disconnected; } ;
struct TYPE_9__ {int flags; } ;

/* Variables and functions */
 int C_OK ; 
 int SENTINEL_INFO_PERIOD ; 
 int SENTINEL_MAX_PENDING_COMMANDS ; 
 int SENTINEL_PING_PERIOD ; 
 int SENTINEL_PUBLISH_PERIOD ; 
 int SRI_FAILOVER_IN_PROGRESS ; 
 int SRI_O_DOWN ; 
 int SRI_SENTINEL ; 
 int SRI_SLAVE ; 
 int mstime () ; 
 int redisAsyncCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelInfoReplyCallback ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  sentinelSendHello (TYPE_3__*) ; 
 int /*<<< orphan*/  sentinelSendPing (TYPE_3__*) ; 

void sentinelSendPeriodicCommands(sentinelRedisInstance *ri) {
    mstime_t now = mstime();
    mstime_t info_period, ping_period;
    int retval;

    /* Return ASAP if we have already a PING or INFO already pending, or
     * in the case the instance is not properly connected. */
    if (ri->link->disconnected) return;

    /* For INFO, PING, PUBLISH that are not critical commands to send we
     * also have a limit of SENTINEL_MAX_PENDING_COMMANDS. We don't
     * want to use a lot of memory just because a link is not working
     * properly (note that anyway there is a redundant protection about this,
     * that is, the link will be disconnected and reconnected if a long
     * timeout condition is detected. */
    if (ri->link->pending_commands >=
        SENTINEL_MAX_PENDING_COMMANDS * ri->link->refcount) return;

    /* If this is a slave of a master in O_DOWN condition we start sending
     * it INFO every second, instead of the usual SENTINEL_INFO_PERIOD
     * period. In this state we want to closely monitor slaves in case they
     * are turned into masters by another Sentinel, or by the sysadmin.
     *
     * Similarly we monitor the INFO output more often if the slave reports
     * to be disconnected from the master, so that we can have a fresh
     * disconnection time figure. */
    if ((ri->flags & SRI_SLAVE) &&
        ((ri->master->flags & (SRI_O_DOWN|SRI_FAILOVER_IN_PROGRESS)) ||
         (ri->master_link_down_time != 0)))
    {
        info_period = 1000;
    } else {
        info_period = SENTINEL_INFO_PERIOD;
    }

    /* We ping instances every time the last received pong is older than
     * the configured 'down-after-milliseconds' time, but every second
     * anyway if 'down-after-milliseconds' is greater than 1 second. */
    ping_period = ri->down_after_period;
    if (ping_period > SENTINEL_PING_PERIOD) ping_period = SENTINEL_PING_PERIOD;

    /* Send INFO to masters and slaves, not sentinels. */
    if ((ri->flags & SRI_SENTINEL) == 0 &&
        (ri->info_refresh == 0 ||
        (now - ri->info_refresh) > info_period))
    {
        retval = redisAsyncCommand(ri->link->cc,
            sentinelInfoReplyCallback, ri, "%s",
            sentinelInstanceMapCommand(ri,"INFO"));
        if (retval == C_OK) ri->link->pending_commands++;
    }

    /* Send PING to all the three kinds of instances. */
    if ((now - ri->link->last_pong_time) > ping_period &&
               (now - ri->link->last_ping_time) > ping_period/2) {
        sentinelSendPing(ri);
    }

    /* PUBLISH hello messages to all the three kinds of instances. */
    if ((now - ri->last_pub_time) > SENTINEL_PUBLISH_PERIOD) {
        sentinelSendHello(ri);
    }
}