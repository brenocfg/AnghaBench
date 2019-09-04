#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct rewriteConfigState {int dummy; } ;
struct TYPE_8__ {scalar_t__ down_after_period; scalar_t__ failover_timeout; long notification_script; long client_reconfig_script; long auth_pass; int /*<<< orphan*/  name; int /*<<< orphan*/  renamed_commands; int /*<<< orphan*/ * runid; TYPE_2__* addr; int /*<<< orphan*/  sentinels; int /*<<< orphan*/  slaves; scalar_t__ leader_epoch; scalar_t__ config_epoch; int /*<<< orphan*/  parallel_syncs; int /*<<< orphan*/  quorum; } ;
typedef  TYPE_1__ sentinelRedisInstance ;
struct TYPE_9__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ sentinelAddr ;
typedef  void* sds ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_10__ {unsigned long long myid; scalar_t__ deny_scripts_reconfig; unsigned long long announce_port; scalar_t__ announce_ip; scalar_t__ current_epoch; int /*<<< orphan*/  masters; } ;

/* Variables and functions */
 scalar_t__ SENTINEL_DEFAULT_DENY_SCRIPTS_RECONFIG ; 
 scalar_t__ SENTINEL_DEFAULT_DOWN_AFTER ; 
 scalar_t__ SENTINEL_DEFAULT_FAILOVER_TIMEOUT ; 
 int /*<<< orphan*/  SENTINEL_DEFAULT_PARALLEL_SYNCS ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 void* dictGetKey (int /*<<< orphan*/ *) ; 
 void* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rewriteConfigRewriteLine (struct rewriteConfigState*,char*,void*,int) ; 
 void* sdscatprintf (int /*<<< orphan*/ ,char*,...) ; 
 void* sdscatrepr (void*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdslen (scalar_t__) ; 
 void* sdsnew (char*) ; 
 TYPE_7__ sentinel ; 
 scalar_t__ sentinelAddrIsEqual (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* sentinelGetCurrentMasterAddress (TYPE_1__*) ; 

void rewriteConfigSentinelOption(struct rewriteConfigState *state) {
    dictIterator *di, *di2;
    dictEntry *de;
    sds line;

    /* sentinel unique ID. */
    line = sdscatprintf(sdsempty(), "sentinel myid %s", sentinel.myid);
    rewriteConfigRewriteLine(state,"sentinel",line,1);

    /* sentinel deny-scripts-reconfig. */
    line = sdscatprintf(sdsempty(), "sentinel deny-scripts-reconfig %s",
        sentinel.deny_scripts_reconfig ? "yes" : "no");
    rewriteConfigRewriteLine(state,"sentinel",line,
        sentinel.deny_scripts_reconfig != SENTINEL_DEFAULT_DENY_SCRIPTS_RECONFIG);

    /* For every master emit a "sentinel monitor" config entry. */
    di = dictGetIterator(sentinel.masters);
    while((de = dictNext(di)) != NULL) {
        sentinelRedisInstance *master, *ri;
        sentinelAddr *master_addr;

        /* sentinel monitor */
        master = dictGetVal(de);
        master_addr = sentinelGetCurrentMasterAddress(master);
        line = sdscatprintf(sdsempty(),"sentinel monitor %s %s %d %d",
            master->name, master_addr->ip, master_addr->port,
            master->quorum);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel down-after-milliseconds */
        if (master->down_after_period != SENTINEL_DEFAULT_DOWN_AFTER) {
            line = sdscatprintf(sdsempty(),
                "sentinel down-after-milliseconds %s %ld",
                master->name, (long) master->down_after_period);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel failover-timeout */
        if (master->failover_timeout != SENTINEL_DEFAULT_FAILOVER_TIMEOUT) {
            line = sdscatprintf(sdsempty(),
                "sentinel failover-timeout %s %ld",
                master->name, (long) master->failover_timeout);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel parallel-syncs */
        if (master->parallel_syncs != SENTINEL_DEFAULT_PARALLEL_SYNCS) {
            line = sdscatprintf(sdsempty(),
                "sentinel parallel-syncs %s %d",
                master->name, master->parallel_syncs);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel notification-script */
        if (master->notification_script) {
            line = sdscatprintf(sdsempty(),
                "sentinel notification-script %s %s",
                master->name, master->notification_script);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel client-reconfig-script */
        if (master->client_reconfig_script) {
            line = sdscatprintf(sdsempty(),
                "sentinel client-reconfig-script %s %s",
                master->name, master->client_reconfig_script);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel auth-pass */
        if (master->auth_pass) {
            line = sdscatprintf(sdsempty(),
                "sentinel auth-pass %s %s",
                master->name, master->auth_pass);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }

        /* sentinel config-epoch */
        line = sdscatprintf(sdsempty(),
            "sentinel config-epoch %s %llu",
            master->name, (unsigned long long) master->config_epoch);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel leader-epoch */
        line = sdscatprintf(sdsempty(),
            "sentinel leader-epoch %s %llu",
            master->name, (unsigned long long) master->leader_epoch);
        rewriteConfigRewriteLine(state,"sentinel",line,1);

        /* sentinel known-slave */
        di2 = dictGetIterator(master->slaves);
        while((de = dictNext(di2)) != NULL) {
            sentinelAddr *slave_addr;

            ri = dictGetVal(de);
            slave_addr = ri->addr;

            /* If master_addr (obtained using sentinelGetCurrentMasterAddress()
             * so it may be the address of the promoted slave) is equal to this
             * slave's address, a failover is in progress and the slave was
             * already successfully promoted. So as the address of this slave
             * we use the old master address instead. */
            if (sentinelAddrIsEqual(slave_addr,master_addr))
                slave_addr = master->addr;
            line = sdscatprintf(sdsempty(),
                "sentinel known-replica %s %s %d",
                master->name, slave_addr->ip, slave_addr->port);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);

        /* sentinel known-sentinel */
        di2 = dictGetIterator(master->sentinels);
        while((de = dictNext(di2)) != NULL) {
            ri = dictGetVal(de);
            if (ri->runid == NULL) continue;
            line = sdscatprintf(sdsempty(),
                "sentinel known-sentinel %s %s %d %s",
                master->name, ri->addr->ip, ri->addr->port, ri->runid);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);

        /* sentinel rename-command */
        di2 = dictGetIterator(master->renamed_commands);
        while((de = dictNext(di2)) != NULL) {
            sds oldname = dictGetKey(de);
            sds newname = dictGetVal(de);
            line = sdscatprintf(sdsempty(),
                "sentinel rename-command %s %s %s",
                master->name, oldname, newname);
            rewriteConfigRewriteLine(state,"sentinel",line,1);
        }
        dictReleaseIterator(di2);
    }

    /* sentinel current-epoch is a global state valid for all the masters. */
    line = sdscatprintf(sdsempty(),
        "sentinel current-epoch %llu", (unsigned long long) sentinel.current_epoch);
    rewriteConfigRewriteLine(state,"sentinel",line,1);

    /* sentinel announce-ip. */
    if (sentinel.announce_ip) {
        line = sdsnew("sentinel announce-ip ");
        line = sdscatrepr(line, sentinel.announce_ip, sdslen(sentinel.announce_ip));
        rewriteConfigRewriteLine(state,"sentinel",line,1);
    }

    /* sentinel announce-port. */
    if (sentinel.announce_port) {
        line = sdscatprintf(sdsempty(),"sentinel announce-port %d",
                            sentinel.announce_port);
        rewriteConfigRewriteLine(state,"sentinel",line,1);
    }

    dictReleaseIterator(di);
}