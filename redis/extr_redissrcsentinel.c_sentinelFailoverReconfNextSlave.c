#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; int parallel_syncs; scalar_t__ slave_reconf_sent_time; TYPE_3__* promoted_slave; TYPE_1__* link; int /*<<< orphan*/  slaves; } ;
typedef  TYPE_4__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_12__ {TYPE_2__* addr; } ;
struct TYPE_11__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
struct TYPE_10__ {scalar_t__ disconnected; } ;

/* Variables and functions */
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 scalar_t__ SENTINEL_SLAVE_RECONF_TIMEOUT ; 
 int SRI_PROMOTED ; 
 int SRI_RECONF_DONE ; 
 int SRI_RECONF_INPROG ; 
 int SRI_RECONF_SENT ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_4__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 scalar_t__ mstime () ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_4__*,char*) ; 
 int /*<<< orphan*/  sentinelFailoverDetectEnd (TYPE_4__*) ; 
 int sentinelSendSlaveOf (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sentinelFailoverReconfNextSlave(sentinelRedisInstance *master) {
    dictIterator *di;
    dictEntry *de;
    int in_progress = 0;

    di = dictGetIterator(master->slaves);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *slave = dictGetVal(de);

        if (slave->flags & (SRI_RECONF_SENT|SRI_RECONF_INPROG))
            in_progress++;
    }
    dictReleaseIterator(di);

    di = dictGetIterator(master->slaves);
    while(in_progress < master->parallel_syncs &&
          (de = dictNext(di)) != NULL)
    {
        sentinelRedisInstance *slave = dictGetVal(de);
        int retval;

        /* Skip the promoted slave, and already configured slaves. */
        if (slave->flags & (SRI_PROMOTED|SRI_RECONF_DONE)) continue;

        /* If too much time elapsed without the slave moving forward to
         * the next state, consider it reconfigured even if it is not.
         * Sentinels will detect the slave as misconfigured and fix its
         * configuration later. */
        if ((slave->flags & SRI_RECONF_SENT) &&
            (mstime() - slave->slave_reconf_sent_time) >
            SENTINEL_SLAVE_RECONF_TIMEOUT)
        {
            sentinelEvent(LL_NOTICE,"-slave-reconf-sent-timeout",slave,"%@");
            slave->flags &= ~SRI_RECONF_SENT;
            slave->flags |= SRI_RECONF_DONE;
        }

        /* Nothing to do for instances that are disconnected or already
         * in RECONF_SENT state. */
        if (slave->flags & (SRI_RECONF_SENT|SRI_RECONF_INPROG)) continue;
        if (slave->link->disconnected) continue;

        /* Send SLAVEOF <new master>. */
        retval = sentinelSendSlaveOf(slave,
                master->promoted_slave->addr->ip,
                master->promoted_slave->addr->port);
        if (retval == C_OK) {
            slave->flags |= SRI_RECONF_SENT;
            slave->slave_reconf_sent_time = mstime();
            sentinelEvent(LL_NOTICE,"+slave-reconf-sent",slave,"%@");
            in_progress++;
        }
    }
    dictReleaseIterator(di);

    /* Check if all the slaves are reconfigured and handle timeout. */
    sentinelFailoverDetectEnd(master);
}