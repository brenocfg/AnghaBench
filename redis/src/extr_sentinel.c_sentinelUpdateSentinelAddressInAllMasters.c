#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int flags; int /*<<< orphan*/  addr; TYPE_5__* link; int /*<<< orphan*/  runid; int /*<<< orphan*/  sentinels; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_10__ {int /*<<< orphan*/ * pc; int /*<<< orphan*/ * cc; } ;
struct TYPE_9__ {int /*<<< orphan*/  masters; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int SRI_SENTINEL ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dupSentinelAddr (int /*<<< orphan*/ ) ; 
 TYPE_1__* getSentinelRedisInstanceByAddrAndRunID (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instanceLinkCloseConnection (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releaseSentinelAddr (int /*<<< orphan*/ ) ; 
 TYPE_4__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  serverAssert (int) ; 

int sentinelUpdateSentinelAddressInAllMasters(sentinelRedisInstance *ri) {
    serverAssert(ri->flags & SRI_SENTINEL);
    dictIterator *di;
    dictEntry *de;
    int reconfigured = 0;

    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master = dictGetVal(de), *match;
        match = getSentinelRedisInstanceByAddrAndRunID(master->sentinels,
                                                       NULL,0,ri->runid);
        /* If there is no match, this master does not know about this
         * Sentinel, try with the next one. */
        if (match == NULL) continue;

        /* Disconnect the old links if connected. */
        if (match->link->cc != NULL)
            instanceLinkCloseConnection(match->link,match->link->cc);
        if (match->link->pc != NULL)
            instanceLinkCloseConnection(match->link,match->link->pc);

        if (match == ri) continue; /* Address already updated for it. */

        /* Update the address of the matching Sentinel by copying the address
         * of the Sentinel object that received the address update. */
        releaseSentinelAddr(match->addr);
        match->addr = dupSentinelAddr(ri->addr);
        reconfigured++;
    }
    dictReleaseIterator(di);
    if (reconfigured)
        sentinelEvent(LL_NOTICE,"+sentinel-address-update", ri,
                    "%@ %d additional matching instances", reconfigured);
    return reconfigured;
}