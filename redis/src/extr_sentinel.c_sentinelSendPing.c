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
struct TYPE_7__ {TYPE_1__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_6__ {scalar_t__ last_ping_time; scalar_t__ act_ping_time; int /*<<< orphan*/  pending_commands; int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int C_OK ; 
 scalar_t__ mstime () ; 
 int redisAsyncCommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelInstanceMapCommand (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sentinelPingReplyCallback ; 

int sentinelSendPing(sentinelRedisInstance *ri) {
    int retval = redisAsyncCommand(ri->link->cc,
        sentinelPingReplyCallback, ri, "%s",
        sentinelInstanceMapCommand(ri,"PING"));
    if (retval == C_OK) {
        ri->link->pending_commands++;
        ri->link->last_ping_time = mstime();
        /* We update the active ping time only if we received the pong for
         * the previous ping, otherwise we are technically waiting since the
         * first ping that did not receive a reply. */
        if (ri->link->act_ping_time == 0)
            ri->link->act_ping_time = ri->link->last_ping_time;
        return 1;
    } else {
        return 0;
    }
}