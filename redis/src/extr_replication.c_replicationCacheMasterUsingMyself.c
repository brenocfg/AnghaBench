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
struct TYPE_4__ {TYPE_1__* master; TYPE_1__* cached_master; int /*<<< orphan*/  replid; int /*<<< orphan*/  master_repl_offset; int /*<<< orphan*/  master_initial_offset; } ;
struct TYPE_3__ {int /*<<< orphan*/  replid; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  replicationCreateMasterClient (int /*<<< orphan*/ *,int) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  unlinkClient (TYPE_1__*) ; 

void replicationCacheMasterUsingMyself(void) {
    /* The master client we create can be set to any DBID, because
     * the new master will start its replication stream with SELECT. */
    server.master_initial_offset = server.master_repl_offset;
    replicationCreateMasterClient(NULL,-1);

    /* Use our own ID / offset. */
    memcpy(server.master->replid, server.replid, sizeof(server.replid));

    /* Set as cached master. */
    unlinkClient(server.master);
    server.cached_master = server.master;
    server.master = NULL;
    serverLog(LL_NOTICE,"Before turning into a replica, using my master parameters to synthesize a cached master: I may be able to synchronize with the new master with just a partial transfer.");
}