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
 int REDISMODULE_ERR ; 
 int /*<<< orphan*/  RedisModule_ReplyWithError (int /*<<< orphan*/ *,char const*) ; 

int failTest(RedisModuleCtx *ctx, const char *msg) {
    RedisModule_ReplyWithError(ctx, msg);
    return REDISMODULE_ERR;
}