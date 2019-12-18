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
struct TYPE_2__ {int loading; size_t loading_total_bytes; scalar_t__ loading_loaded_bytes; int /*<<< orphan*/  loading_start_time; } ;

/* Variables and functions */
 int RDBFLAGS_AOF_PREAMBLE ; 
 int RDBFLAGS_REPLICATION ; 
 int /*<<< orphan*/  REDISMODULE_EVENT_LOADING ; 
 int REDISMODULE_SUBEVENT_LOADING_AOF_START ; 
 int REDISMODULE_SUBEVENT_LOADING_RDB_START ; 
 int REDISMODULE_SUBEVENT_LOADING_REPL_START ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void startLoading(size_t size, int rdbflags) {
    /* Load the DB */
    server.loading = 1;
    server.loading_start_time = time(NULL);
    server.loading_loaded_bytes = 0;
    server.loading_total_bytes = size;

    /* Fire the loading modules start event. */
    int subevent;
    if (rdbflags & RDBFLAGS_AOF_PREAMBLE)
        subevent = REDISMODULE_SUBEVENT_LOADING_AOF_START;
    else if(rdbflags & RDBFLAGS_REPLICATION)
        subevent = REDISMODULE_SUBEVENT_LOADING_REPL_START;
    else
        subevent = REDISMODULE_SUBEVENT_LOADING_RDB_START;
    moduleFireServerEvent(REDISMODULE_EVENT_LOADING,subevent,NULL);
}