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
 scalar_t__ HelloType ; 
 int HelloTypeRange_RedisCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int) ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_KEYTYPE_MODULE ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int /*<<< orphan*/  REDISMODULE_READ ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_GetBlockedClientReadyKey (int /*<<< orphan*/ *) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_ModuleTypeGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int HelloBlock_Reply(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    RedisModuleString *keyname = RedisModule_GetBlockedClientReadyKey(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,keyname,REDISMODULE_READ);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_MODULE ||
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        RedisModule_CloseKey(key);
        return REDISMODULE_ERR;
    }

    /* In case the key is able to serve our blocked client, let's directly
     * use our original command implementation to make this example simpler. */
    RedisModule_CloseKey(key);
    return HelloTypeRange_RedisCommand(ctx,argv,argc-1);
}