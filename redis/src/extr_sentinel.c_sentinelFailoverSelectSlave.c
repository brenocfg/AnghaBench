#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  failover_state_change_time; int /*<<< orphan*/  failover_state; struct TYPE_7__* promoted_slave; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ sentinelRedisInstance ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE ; 
 int /*<<< orphan*/  SRI_PROMOTED ; 
 int /*<<< orphan*/  mstime () ; 
 int /*<<< orphan*/  sentinelAbortFailover (TYPE_1__*) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 
 TYPE_1__* sentinelSelectSlave (TYPE_1__*) ; 

void sentinelFailoverSelectSlave(sentinelRedisInstance *ri) {
    sentinelRedisInstance *slave = sentinelSelectSlave(ri);

    /* We don't handle the timeout in this state as the function aborts
     * the failover or go forward in the next state. */
    if (slave == NULL) {
        sentinelEvent(LL_WARNING,"-failover-abort-no-good-slave",ri,"%@");
        sentinelAbortFailover(ri);
    } else {
        sentinelEvent(LL_WARNING,"+selected-slave",slave,"%@");
        slave->flags |= SRI_PROMOTED;
        ri->promoted_slave = slave;
        ri->failover_state = SENTINEL_FAILOVER_STATE_SEND_SLAVEOF_NOONE;
        ri->failover_state_change_time = mstime();
        sentinelEvent(LL_NOTICE,"+failover-state-send-slaveof-noone",
            slave, "%@");
    }
}