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
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {TYPE_2__* cached_master; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLIENT_MASTER ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  freeClient (TYPE_2__*) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*) ; 

void replicationDiscardCachedMaster(void) {
    if (server.cached_master == NULL) return;

    serverLog(LL_NOTICE,"Discarding previously cached master state.");
    server.cached_master->flags &= ~CLIENT_MASTER;
    freeClient(server.cached_master);
    server.cached_master = NULL;
}