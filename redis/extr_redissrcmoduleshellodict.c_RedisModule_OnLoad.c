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
 int /*<<< orphan*/  Keyspace ; 
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 scalar_t__ REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_CreateDict (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmd_GET ; 
 int /*<<< orphan*/  cmd_KEYRANGE ; 
 int /*<<< orphan*/  cmd_SET ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"hellodict",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.set",
        cmd_SET,"write deny-oom",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.get",
        cmd_GET,"readonly",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellodict.keyrange",
        cmd_KEYRANGE,"readonly",1,1,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    /* Create our global dictionray. Here we'll set our keys and values. */
    Keyspace = RedisModule_CreateDict(NULL);

    return REDISMODULE_OK;
}