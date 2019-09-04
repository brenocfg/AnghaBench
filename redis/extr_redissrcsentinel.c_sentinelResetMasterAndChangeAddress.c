#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  quorum; scalar_t__ s_down_since_time; scalar_t__ o_down_since_time; TYPE_2__* addr; int /*<<< orphan*/  slaves; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_17__ {char* ip; int port; } ;
typedef  TYPE_2__ sentinelAddr ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;

/* Variables and functions */
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  SENTINEL_RESET_NO_SENTINELS ; 
 int /*<<< orphan*/  SRI_SLAVE ; 
 TYPE_2__* createSentinelAddr (char*,int) ; 
 TYPE_1__* createSentinelRedisInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releaseSentinelAddr (TYPE_2__*) ; 
 scalar_t__ sentinelAddrIsEqual (TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  sentinelFlushConfig () ; 
 int /*<<< orphan*/  sentinelResetMaster (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__**) ; 
 TYPE_2__** zrealloc (TYPE_2__**,int) ; 

int sentinelResetMasterAndChangeAddress(sentinelRedisInstance *master, char *ip, int port) {
    sentinelAddr *oldaddr, *newaddr;
    sentinelAddr **slaves = NULL;
    int numslaves = 0, j;
    dictIterator *di;
    dictEntry *de;

    newaddr = createSentinelAddr(ip,port);
    if (newaddr == NULL) return C_ERR;

    /* Make a list of slaves to add back after the reset.
     * Don't include the one having the address we are switching to. */
    di = dictGetIterator(master->slaves);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *slave = dictGetVal(de);

        if (sentinelAddrIsEqual(slave->addr,newaddr)) continue;
        slaves = zrealloc(slaves,sizeof(sentinelAddr*)*(numslaves+1));
        slaves[numslaves++] = createSentinelAddr(slave->addr->ip,
                                                 slave->addr->port);
    }
    dictReleaseIterator(di);

    /* If we are switching to a different address, include the old address
     * as a slave as well, so that we'll be able to sense / reconfigure
     * the old master. */
    if (!sentinelAddrIsEqual(newaddr,master->addr)) {
        slaves = zrealloc(slaves,sizeof(sentinelAddr*)*(numslaves+1));
        slaves[numslaves++] = createSentinelAddr(master->addr->ip,
                                                 master->addr->port);
    }

    /* Reset and switch address. */
    sentinelResetMaster(master,SENTINEL_RESET_NO_SENTINELS);
    oldaddr = master->addr;
    master->addr = newaddr;
    master->o_down_since_time = 0;
    master->s_down_since_time = 0;

    /* Add slaves back. */
    for (j = 0; j < numslaves; j++) {
        sentinelRedisInstance *slave;

        slave = createSentinelRedisInstance(NULL,SRI_SLAVE,slaves[j]->ip,
                    slaves[j]->port, master->quorum, master);
        releaseSentinelAddr(slaves[j]);
        if (slave) sentinelEvent(LL_NOTICE,"+slave",slave,"%@");
    }
    zfree(slaves);

    /* Release the old address at the end so we are safe even if the function
     * gets the master->addr->ip and master->addr->port as arguments. */
    releaseSentinelAddr(oldaddr);
    sentinelFlushConfig();
    return C_OK;
}