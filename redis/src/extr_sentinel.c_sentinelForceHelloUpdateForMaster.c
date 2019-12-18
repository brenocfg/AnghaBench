#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int flags; scalar_t__ last_pub_time; int /*<<< orphan*/  slaves; int /*<<< orphan*/  sentinels; } ;
typedef  TYPE_1__ sentinelRedisInstance ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ SENTINEL_PUBLISH_PERIOD ; 
 int SRI_MASTER ; 
 int /*<<< orphan*/  sentinelForceHelloUpdateDictOfRedisInstances (int /*<<< orphan*/ ) ; 

int sentinelForceHelloUpdateForMaster(sentinelRedisInstance *master) {
    if (!(master->flags & SRI_MASTER)) return C_ERR;
    if (master->last_pub_time >= (SENTINEL_PUBLISH_PERIOD+1))
        master->last_pub_time -= (SENTINEL_PUBLISH_PERIOD+1);
    sentinelForceHelloUpdateDictOfRedisInstances(master->sentinels);
    sentinelForceHelloUpdateDictOfRedisInstances(master->slaves);
    return C_OK;
}