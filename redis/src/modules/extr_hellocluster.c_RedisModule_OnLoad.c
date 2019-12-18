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
 int /*<<< orphan*/  ListCommand_RedisCommand ; 
 int /*<<< orphan*/  MSGTYPE_PING ; 
 int /*<<< orphan*/  MSGTYPE_PONG ; 
 int /*<<< orphan*/  PingReceiver ; 
 int /*<<< orphan*/  PingallCommand_RedisCommand ; 
 int /*<<< orphan*/  PongReceiver ; 
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 int /*<<< orphan*/  REDISMODULE_CLUSTER_FLAG_NO_REDIRECTION ; 
 scalar_t__ REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_RegisterClusterMessageReceiver (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_SetClusterFlags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx,"hellocluster",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellocluster.pingall",
        PingallCommand_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hellocluster.list",
        ListCommand_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    /* Disable Redis Cluster sharding and redirections. This way every node
     * will be able to access every possible key, regardless of the hash slot.
     * This way the PING message handler will be able to increment a specific
     * variable. Normally you do that in order for the distributed system
     * you create as a module to have total freedom in the keyspace
     * manipulation. */
    RedisModule_SetClusterFlags(ctx,REDISMODULE_CLUSTER_FLAG_NO_REDIRECTION);

    /* Register our handlers for different message types. */
    RedisModule_RegisterClusterMessageReceiver(ctx,MSGTYPE_PING,PingReceiver);
    RedisModule_RegisterClusterMessageReceiver(ctx,MSGTYPE_PONG,PongReceiver);
    return REDISMODULE_OK;
}