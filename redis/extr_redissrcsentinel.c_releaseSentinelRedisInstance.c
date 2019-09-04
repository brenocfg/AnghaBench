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
struct TYPE_7__ {int flags; TYPE_1__* master; int /*<<< orphan*/  renamed_commands; int /*<<< orphan*/  addr; int /*<<< orphan*/  info; int /*<<< orphan*/  auth_pass; int /*<<< orphan*/  leader; int /*<<< orphan*/  slave_master_host; int /*<<< orphan*/  client_reconfig_script; int /*<<< orphan*/  notification_script; int /*<<< orphan*/  runid; int /*<<< orphan*/  name; int /*<<< orphan*/  link; int /*<<< orphan*/  slaves; int /*<<< orphan*/  sentinels; } ;
typedef  TYPE_2__ sentinelRedisInstance ;
struct TYPE_6__ {int /*<<< orphan*/ * promoted_slave; } ;

/* Variables and functions */
 int SRI_PROMOTED ; 
 int SRI_SLAVE ; 
 int /*<<< orphan*/  dictRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releaseInstanceLink (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  releaseSentinelAddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfree (TYPE_2__*) ; 

void releaseSentinelRedisInstance(sentinelRedisInstance *ri) {
    /* Release all its slaves or sentinels if any. */
    dictRelease(ri->sentinels);
    dictRelease(ri->slaves);

    /* Disconnect the instance. */
    releaseInstanceLink(ri->link,ri);

    /* Free other resources. */
    sdsfree(ri->name);
    sdsfree(ri->runid);
    sdsfree(ri->notification_script);
    sdsfree(ri->client_reconfig_script);
    sdsfree(ri->slave_master_host);
    sdsfree(ri->leader);
    sdsfree(ri->auth_pass);
    sdsfree(ri->info);
    releaseSentinelAddr(ri->addr);
    dictRelease(ri->renamed_commands);

    /* Clear state into the master if needed. */
    if ((ri->flags & SRI_SLAVE) && (ri->flags & SRI_PROMOTED) && ri->master)
        ri->master->promoted_slave = NULL;

    zfree(ri);
}