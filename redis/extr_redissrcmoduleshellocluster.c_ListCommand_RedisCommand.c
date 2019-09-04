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
 int /*<<< orphan*/  REDISMODULE_NODE_ID_LEN ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_FreeClusterNodesList (char**) ; 
 int /*<<< orphan*/  RedisModule_GetClusterNodeInfo (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 char** RedisModule_GetClusterNodesList (int /*<<< orphan*/ *,size_t*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithStringBuffer (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

int ListCommand_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    size_t numnodes;
    char **ids = RedisModule_GetClusterNodesList(ctx,&numnodes);
    if (ids == NULL) {
        return RedisModule_ReplyWithError(ctx,"Cluster not enabled");
    }

    RedisModule_ReplyWithArray(ctx,numnodes);
    for (size_t j = 0; j < numnodes; j++) {
        int port;
        RedisModule_GetClusterNodeInfo(ctx,ids[j],NULL,NULL,&port,NULL);
        RedisModule_ReplyWithArray(ctx,2);
        RedisModule_ReplyWithStringBuffer(ctx,ids[j],REDISMODULE_NODE_ID_LEN);
        RedisModule_ReplyWithLongLong(ctx,port);
    }
    RedisModule_FreeClusterNodesList(ids);
    return REDISMODULE_OK;
}