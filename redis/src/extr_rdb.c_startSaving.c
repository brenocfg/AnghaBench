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
struct TYPE_2__ {scalar_t__ pid; } ;

/* Variables and functions */
 int RDBFLAGS_AOF_PREAMBLE ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_PERSISTENCE ; 
 int REDISMODULE_SUBEVENT_PERSISTENCE_AOF_START ; 
 int REDISMODULE_SUBEVENT_PERSISTENCE_RDB_START ; 
 int REDISMODULE_SUBEVENT_PERSISTENCE_SYNC_RDB_START ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void startSaving(int rdbflags) {
    /* Fire the persistence modules end event. */
    int subevent;
    if (rdbflags & RDBFLAGS_AOF_PREAMBLE)
        subevent = REDISMODULE_SUBEVENT_PERSISTENCE_AOF_START;
    else if (getpid()!=server.pid)
        subevent = REDISMODULE_SUBEVENT_PERSISTENCE_RDB_START;
    else
        subevent = REDISMODULE_SUBEVENT_PERSISTENCE_SYNC_RDB_START;
    moduleFireServerEvent(REDISMODULE_EVENT_PERSISTENCE,subevent,NULL);
}