#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_FreeDict (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clearEvents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * event_log ; 

int RedisModule_OnUnload(RedisModuleCtx *ctx) {
    clearEvents(ctx);
    RedisModule_FreeDict(ctx, event_log);
    event_log = NULL;
    return REDISMODULE_OK;
}