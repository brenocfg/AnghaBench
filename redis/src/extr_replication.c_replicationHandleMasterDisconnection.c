#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ repl_state; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  repl_down_since; int /*<<< orphan*/ * master; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_EVENT_MASTER_LINK_CHANGE ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_MASTER_LINK_DOWN ; 
 scalar_t__ REPL_STATE_CONNECT ; 
 scalar_t__ REPL_STATE_CONNECTED ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void replicationHandleMasterDisconnection(void) {
    /* Fire the master link modules event. */
    if (server.repl_state == REPL_STATE_CONNECTED)
        moduleFireServerEvent(REDISMODULE_EVENT_MASTER_LINK_CHANGE,
                              REDISMODULE_SUBEVENT_MASTER_LINK_DOWN,
                              NULL);

    server.master = NULL;
    server.repl_state = REPL_STATE_CONNECT;
    server.repl_down_since = server.unixtime;
    /* We lost connection with our master, don't disconnect slaves yet,
     * maybe we'll be able to PSYNC with our master later. We'll disconnect
     * the slaves only if we'll have to do a full resync with our master. */
}