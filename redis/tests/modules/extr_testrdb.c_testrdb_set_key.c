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
typedef  int /*<<< orphan*/  RedisModuleKey ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_ModuleTypeGetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ModuleTypeSetValue (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_RetainString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  testrdb_type ; 

int testrdb_set_key(RedisModuleCtx *ctx, RedisModuleString **argv, int argc)
{
    if (argc != 3){
        RedisModule_WrongArity(ctx);
        return REDISMODULE_OK;
    }

    RedisModuleKey *key = RedisModule_OpenKey(ctx, argv[1], REDISMODULE_WRITE);
    RedisModuleString *str = RedisModule_ModuleTypeGetValue(key);
    if (str)
        RedisModule_FreeString(ctx, str);
    RedisModule_ModuleTypeSetValue(key, testrdb_type, argv[2]);
    RedisModule_RetainString(ctx, argv[2]);
    RedisModule_CloseKey(key);
    RedisModule_ReplyWithLongLong(ctx, 1);
    return REDISMODULE_OK;
}