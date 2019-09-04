#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ failover_state_change_time; scalar_t__ failover_timeout; int /*<<< orphan*/  failover_state; struct TYPE_8__* promoted_slave; TYPE_1__* link; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_7__ {scalar_t__ disconnected; } ;

/* Variables and functions */
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SENTINEL_FAILOVER_STATE_WAIT_PROMOTION ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  sentinelAbortFailover (TYPE_2__*) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_2__*,char*) ; 
 int sentinelSendSlaveOf (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sentinelFailoverSendSlaveOfNoOne(sentinelRedisInstance *ri) {
    int retval;

    /* We can't send the command to the promoted slave if it is now
     * disconnected. Retry again and again with this state until the timeout
     * is reached, then abort the failover. */
    if (ri->promoted_slave->link->disconnected) {
        if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
            sentinelEvent(LL_WARNING,"-failover-abort-slave-timeout",ri,"%@");
            sentinelAbortFailover(ri);
        }
        return;
    }

    /* Send SLAVEOF NO ONE command to turn the slave into a master.
     * We actually register a generic callback for this command as we don't
     * really care about the reply. We check if it worked indirectly observing
     * if INFO returns a different role (master instead of slave). */
    retval = sentinelSendSlaveOf(ri->promoted_slave,NULL,0);
    if (retval != C_OK) return;
    sentinelEvent(LL_NOTICE, "+failover-state-wait-promotion",
        ri->promoted_slave,"%@");
    ri->failover_state = SENTINEL_FAILOVER_STATE_WAIT_PROMOTION;
    ri->failover_state_change_time = mstime();
}