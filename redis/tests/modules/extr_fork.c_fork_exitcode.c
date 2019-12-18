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
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  exitted_with_code ; 

int fork_exitcode(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    UNUSED(argv);
    UNUSED(argc);
    RedisModule_ReplyWithLongLong(ctx, exitted_with_code);
    return REDISMODULE_OK;
}