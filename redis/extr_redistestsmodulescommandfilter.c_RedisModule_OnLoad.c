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
 int /*<<< orphan*/  CommandFilter_CommandFilter ; 
 int /*<<< orphan*/  CommandFilter_LogCommand ; 
 int /*<<< orphan*/  CommandFilter_PingCommand ; 
 int /*<<< orphan*/  CommandFilter_UnregisterCommand ; 
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 int /*<<< orphan*/  REDISMODULE_CMDFILTER_NOSELF ; 
 scalar_t__ REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int) ; 
 int /*<<< orphan*/  RedisModule_CreateStringFromString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_Log (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/ * RedisModule_RegisterCommandFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int /*<<< orphan*/ * filter ; 
 int /*<<< orphan*/  log_command_name ; 
 int /*<<< orphan*/  log_key_name ; 
 int /*<<< orphan*/  ping_command_name ; 
 int /*<<< orphan*/  unregister_command_name ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"commandfilter",1,REDISMODULE_APIVER_1)
            == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (argc != 2) {
        RedisModule_Log(ctx, "warning", "Log key name not specified");
        return REDISMODULE_ERR;
    }

    long long noself = 0;
    log_key_name = RedisModule_CreateStringFromString(ctx, argv[0]);
    RedisModule_StringToLongLong(argv[1], &noself);

    if (RedisModule_CreateCommand(ctx,log_command_name,
                CommandFilter_LogCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,ping_command_name,
                CommandFilter_PingCommand,"deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,unregister_command_name,
                CommandFilter_UnregisterCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
            return REDISMODULE_ERR;

    if ((filter = RedisModule_RegisterCommandFilter(ctx, CommandFilter_CommandFilter, 
                    noself ? REDISMODULE_CMDFILTER_NOSELF : 0))
            == NULL) return REDISMODULE_ERR;

    return REDISMODULE_OK;
}