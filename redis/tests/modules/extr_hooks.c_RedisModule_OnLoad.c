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
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 scalar_t__ REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModuleEvent_ClientChange ; 
 int /*<<< orphan*/  RedisModuleEvent_CronLoop ; 
 int /*<<< orphan*/  RedisModuleEvent_FlushDB ; 
 int /*<<< orphan*/  RedisModuleEvent_Loading ; 
 int /*<<< orphan*/  RedisModuleEvent_LoadingProgress ; 
 int /*<<< orphan*/  RedisModuleEvent_MasterLinkChange ; 
 int /*<<< orphan*/  RedisModuleEvent_ModuleChange ; 
 int /*<<< orphan*/  RedisModuleEvent_Persistence ; 
 int /*<<< orphan*/  RedisModuleEvent_ReplicaChange ; 
 int /*<<< orphan*/  RedisModuleEvent_ReplicationRoleChanged ; 
 int /*<<< orphan*/  RedisModuleEvent_Shutdown ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_CreateDict (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_SubscribeToServerEvent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clientChangeCallback ; 
 int /*<<< orphan*/  cmdEventCount ; 
 int /*<<< orphan*/  cmdEventLast ; 
 int /*<<< orphan*/  cmdEventsClear ; 
 int /*<<< orphan*/  cronLoopCallback ; 
 int /*<<< orphan*/  event_log ; 
 int /*<<< orphan*/  flushdbCallback ; 
 int /*<<< orphan*/  loadingCallback ; 
 int /*<<< orphan*/  loadingProgressCallback ; 
 int /*<<< orphan*/  moduleChangeCallback ; 
 int /*<<< orphan*/  persistenceCallback ; 
 int /*<<< orphan*/  rasterLinkChangeCallback ; 
 int /*<<< orphan*/  replicationChangeCallback ; 
 int /*<<< orphan*/  roleChangeCallback ; 
 int /*<<< orphan*/  shutdownCallback ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"testhook",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    /* replication related hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ReplicationRoleChanged, roleChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ReplicaChange, replicationChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_MasterLinkChange, rasterLinkChangeCallback);

    /* persistence related hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Persistence, persistenceCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Loading, loadingCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_LoadingProgress, loadingProgressCallback);

    /* other hooks */
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ClientChange, clientChangeCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_FlushDB, flushdbCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_Shutdown, shutdownCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_CronLoop, cronLoopCallback);
    RedisModule_SubscribeToServerEvent(ctx,
        RedisModuleEvent_ModuleChange, moduleChangeCallback);

    event_log = RedisModule_CreateDict(ctx);

    if (RedisModule_CreateCommand(ctx,"hooks.event_count", cmdEventCount,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    if (RedisModule_CreateCommand(ctx,"hooks.event_last", cmdEventLast,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;
    if (RedisModule_CreateCommand(ctx,"hooks.clear", cmdEventsClear,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}