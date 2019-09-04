#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int flags; int role_reported; void* role_reported_time; TYPE_4__* link; int /*<<< orphan*/ * slave_master_host; int /*<<< orphan*/ * runid; int /*<<< orphan*/ * promoted_slave; scalar_t__ failover_start_time; scalar_t__ failover_state_change_time; int /*<<< orphan*/  failover_state; int /*<<< orphan*/ * leader; void* sentinels; void* slaves; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_6__ {void* last_pong_time; void* last_avail_time; scalar_t__ last_ping_time; void* act_ping_time; int /*<<< orphan*/  pc; int /*<<< orphan*/  cc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SENTINEL_FAILOVER_STATE_NONE ; 
 int SENTINEL_GENERATE_EVENT ; 
 int SENTINEL_RESET_NO_SENTINELS ; 
 int SRI_MASTER ; 
 void* dictCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictRelease (void*) ; 
 int /*<<< orphan*/  instanceLinkCloseConnection (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instancesDictType ; 
 void* mstime () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  serverAssert (int) ; 

void sentinelResetMaster(sentinelRedisInstance *ri, int flags) {
    serverAssert(ri->flags & SRI_MASTER);
    dictRelease(ri->slaves);
    ri->slaves = dictCreate(&instancesDictType,NULL);
    if (!(flags & SENTINEL_RESET_NO_SENTINELS)) {
        dictRelease(ri->sentinels);
        ri->sentinels = dictCreate(&instancesDictType,NULL);
    }
    instanceLinkCloseConnection(ri->link,ri->link->cc);
    instanceLinkCloseConnection(ri->link,ri->link->pc);
    ri->flags &= SRI_MASTER;
    if (ri->leader) {
        sdsfree(ri->leader);
        ri->leader = NULL;
    }
    ri->failover_state = SENTINEL_FAILOVER_STATE_NONE;
    ri->failover_state_change_time = 0;
    ri->failover_start_time = 0; /* We can failover again ASAP. */
    ri->promoted_slave = NULL;
    sdsfree(ri->runid);
    sdsfree(ri->slave_master_host);
    ri->runid = NULL;
    ri->slave_master_host = NULL;
    ri->link->act_ping_time = mstime();
    ri->link->last_ping_time = 0;
    ri->link->last_avail_time = mstime();
    ri->link->last_pong_time = mstime();
    ri->role_reported_time = mstime();
    ri->role_reported = SRI_MASTER;
    if (flags & SENTINEL_GENERATE_EVENT)
        sentinelEvent(LL_WARNING,"+reset-master",ri,"%@");
}