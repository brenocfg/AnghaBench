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
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int* RedisModule_GetBlockedClientPrivateData (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int) ; 

int HelloBlock_Reply(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    int *myint = RedisModule_GetBlockedClientPrivateData(ctx);
    return RedisModule_ReplyWithLongLong(ctx,*myint);
}