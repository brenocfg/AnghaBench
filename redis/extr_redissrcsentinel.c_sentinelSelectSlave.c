#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int flags; scalar_t__ s_down_since_time; int down_after_period; scalar_t__ slave_priority; scalar_t__ info_refresh; scalar_t__ master_link_down_time; TYPE_1__* link; int /*<<< orphan*/  slaves; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
typedef  scalar_t__ mstime_t ;
typedef  int /*<<< orphan*/  instance ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_9__ {int last_avail_time; scalar_t__ disconnected; } ;

/* Variables and functions */
 int SENTINEL_INFO_PERIOD ; 
 int SENTINEL_PING_PERIOD ; 
 int SRI_O_DOWN ; 
 int SRI_S_DOWN ; 
 int /*<<< orphan*/  compareSlavesForPromotion ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_2__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int dictSize (int /*<<< orphan*/ ) ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  qsort (TYPE_2__**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 
 TYPE_2__** zmalloc (int) ; 

sentinelRedisInstance *sentinelSelectSlave(sentinelRedisInstance *master) {
    sentinelRedisInstance **instance =
        zmalloc(sizeof(instance[0])*dictSize(master->slaves));
    sentinelRedisInstance *selected = NULL;
    int instances = 0;
    dictIterator *di;
    dictEntry *de;
    mstime_t max_master_down_time = 0;

    if (master->flags & SRI_S_DOWN)
        max_master_down_time += mstime() - master->s_down_since_time;
    max_master_down_time += master->down_after_period * 10;

    di = dictGetIterator(master->slaves);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *slave = dictGetVal(de);
        mstime_t info_validity_time;

        if (slave->flags & (SRI_S_DOWN|SRI_O_DOWN)) continue;
        if (slave->link->disconnected) continue;
        if (mstime() - slave->link->last_avail_time > SENTINEL_PING_PERIOD*5) continue;
        if (slave->slave_priority == 0) continue;

        /* If the master is in SDOWN state we get INFO for slaves every second.
         * Otherwise we get it with the usual period so we need to account for
         * a larger delay. */
        if (master->flags & SRI_S_DOWN)
            info_validity_time = SENTINEL_PING_PERIOD*5;
        else
            info_validity_time = SENTINEL_INFO_PERIOD*3;
        if (mstime() - slave->info_refresh > info_validity_time) continue;
        if (slave->master_link_down_time > max_master_down_time) continue;
        instance[instances++] = slave;
    }
    dictReleaseIterator(di);
    if (instances) {
        qsort(instance,instances,sizeof(sentinelRedisInstance*),
            compareSlavesForPromotion);
        selected = instance[0];
    }
    zfree(instance);
    return selected;
}