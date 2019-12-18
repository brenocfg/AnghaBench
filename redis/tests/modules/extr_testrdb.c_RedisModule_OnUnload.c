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
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ after_str ; 
 scalar_t__ before_str ; 

int RedisModule_OnUnload(RedisModuleCtx *ctx) {
    if (before_str)
        RedisModule_FreeString(ctx, before_str);
    if (after_str)
        RedisModule_FreeString(ctx, after_str);
    return REDISMODULE_OK;
}