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
typedef  scalar_t__ uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  progress; } ;
typedef  TYPE_1__ RedisModuleLoadingProgress ;
typedef  int /*<<< orphan*/  RedisModuleEvent ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  LogNumericEvent (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int /*<<< orphan*/ ) ; 
 scalar_t__ REDISMODULE_SUBEVENT_LOADING_PROGRESS_RDB ; 

void loadingProgressCallback(RedisModuleCtx *ctx, RedisModuleEvent e, uint64_t sub, void *data)
{
    REDISMODULE_NOT_USED(e);

    RedisModuleLoadingProgress *ei = data;
    char *keyname = (sub == REDISMODULE_SUBEVENT_LOADING_PROGRESS_RDB) ?
        "loading-progress-rdb" : "loading-progress-aof";
    LogNumericEvent(ctx, keyname, ei->progress);
}