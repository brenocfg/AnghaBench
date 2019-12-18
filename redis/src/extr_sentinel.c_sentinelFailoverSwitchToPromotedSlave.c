#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* addr; int /*<<< orphan*/  name; struct TYPE_7__* promoted_slave; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_6__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sentinelResetMasterAndChangeAddress (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sentinelFailoverSwitchToPromotedSlave(sentinelRedisInstance *master) {
    sentinelRedisInstance *ref = master->promoted_slave ?
                                 master->promoted_slave : master;

    sentinelEvent(LL_WARNING,"+switch-master",master,"%s %s %d %s %d",
        master->name, master->addr->ip, master->addr->port,
        ref->addr->ip, ref->addr->port);

    sentinelResetMasterAndChangeAddress(master,ref->addr->ip,ref->addr->port);
}