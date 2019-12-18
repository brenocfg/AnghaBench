#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; scalar_t__ failover_state; TYPE_1__* promoted_slave; int /*<<< orphan*/  failover_state_change_time; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 scalar_t__ SENTINEL_FAILOVER_STATE_NONE ; 
 scalar_t__ SENTINEL_FAILOVER_STATE_WAIT_PROMOTION ; 
 int SRI_FAILOVER_IN_PROGRESS ; 
 int SRI_FORCE_FAILOVER ; 
 int /*<<< orphan*/  SRI_PROMOTED ; 
 int /*<<< orphan*/  mstime () ; 
 int /*<<< orphan*/  serverAssert (int) ; 

void sentinelAbortFailover(sentinelRedisInstance *ri) {
    serverAssert(ri->flags & SRI_FAILOVER_IN_PROGRESS);
    serverAssert(ri->failover_state <= SENTINEL_FAILOVER_STATE_WAIT_PROMOTION);

    ri->flags &= ~(SRI_FAILOVER_IN_PROGRESS|SRI_FORCE_FAILOVER);
    ri->failover_state = SENTINEL_FAILOVER_STATE_NONE;
    ri->failover_state_change_time = mstime();
    if (ri->promoted_slave) {
        ri->promoted_slave->flags &= ~SRI_PROMOTED;
        ri->promoted_slave = NULL;
    }
}