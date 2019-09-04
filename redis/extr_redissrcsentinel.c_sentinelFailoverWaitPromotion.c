#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ failover_state_change_time; scalar_t__ failover_timeout; } ;
typedef  TYPE_1__ sentinelRedisInstance ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  sentinelAbortFailover (TYPE_1__*) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 

void sentinelFailoverWaitPromotion(sentinelRedisInstance *ri) {
    /* Just handle the timeout. Switching to the next state is handled
     * by the function parsing the INFO command of the promoted slave. */
    if (mstime() - ri->failover_state_change_time > ri->failover_timeout) {
        sentinelEvent(LL_WARNING,"-failover-abort-slave-timeout",ri,"%@");
        sentinelAbortFailover(ri);
    }
}