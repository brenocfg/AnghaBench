#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int loading_total_bytes; int hz; } ;
struct TYPE_4__ {int member_1; int member_2; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ RedisModuleFlushInfoV1 ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_EVENT_LOADING_PROGRESS ; 
 int /*<<< orphan*/  REDISMODULE_LOADING_PROGRESS_VERSION ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_LOADING_PROGRESS_AOF ; 
 int /*<<< orphan*/  REDISMODULE_SUBEVENT_LOADING_PROGRESS_RDB ; 
 int /*<<< orphan*/  moduleFireServerEvent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_2__ server ; 
 long long ustime () ; 

void processModuleLoadingProgressEvent(int is_aof) {
    long long now = ustime();
    static long long next_event = 0;
    if (now >= next_event) {
        /* Fire the loading progress modules end event. */
        int progress = -1;
        if (server.loading_total_bytes)
            progress = (server.loading_total_bytes<<10) / server.loading_total_bytes;
        RedisModuleFlushInfoV1 fi = {REDISMODULE_LOADING_PROGRESS_VERSION,
                                     server.hz,
                                     progress};
        moduleFireServerEvent(REDISMODULE_EVENT_LOADING_PROGRESS,
                              is_aof?
                                REDISMODULE_SUBEVENT_LOADING_PROGRESS_AOF:
                                REDISMODULE_SUBEVENT_LOADING_PROGRESS_RDB,
                              &fi);
        /* decide when the next event should fire. */
        next_event = now + 1000000 / server.hz;
    }
}