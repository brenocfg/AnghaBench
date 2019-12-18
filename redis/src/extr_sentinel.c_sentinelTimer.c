#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  masters; } ;
struct TYPE_3__ {int hz; } ;

/* Variables and functions */
 int CONFIG_DEFAULT_HZ ; 
 int rand () ; 
 TYPE_2__ sentinel ; 
 int /*<<< orphan*/  sentinelCheckTiltCondition () ; 
 int /*<<< orphan*/  sentinelCollectTerminatedScripts () ; 
 int /*<<< orphan*/  sentinelHandleDictOfRedisInstances (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelKillTimedoutScripts () ; 
 int /*<<< orphan*/  sentinelRunPendingScripts () ; 
 TYPE_1__ server ; 

void sentinelTimer(void) {
    sentinelCheckTiltCondition();
    sentinelHandleDictOfRedisInstances(sentinel.masters);
    sentinelRunPendingScripts();
    sentinelCollectTerminatedScripts();
    sentinelKillTimedoutScripts();

    /* We continuously change the frequency of the Redis "timer interrupt"
     * in order to desynchronize every Sentinel from every other.
     * This non-determinism avoids that Sentinels started at the same time
     * exactly continue to stay synchronized asking to be voted at the
     * same time again and again (resulting in nobody likely winning the
     * election because of split brain voting). */
    server.hz = CONFIG_DEFAULT_HZ + rand() % CONFIG_DEFAULT_HZ;
}