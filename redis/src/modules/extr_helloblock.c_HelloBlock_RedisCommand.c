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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;
typedef  int /*<<< orphan*/  RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  HelloBlock_Disconnected ; 
 int /*<<< orphan*/  HelloBlock_FreeData ; 
 int /*<<< orphan*/  HelloBlock_Reply ; 
 int /*<<< orphan*/  HelloBlock_ThreadMain ; 
 int /*<<< orphan*/  HelloBlock_Timeout ; 
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_AbortBlock (int /*<<< orphan*/ *) ; 
 void** RedisModule_Alloc (int) ; 
 int /*<<< orphan*/ * RedisModule_BlockClient (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_SetDisconnectCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 

int HelloBlock_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3) return RedisModule_WrongArity(ctx);
    long long delay;
    long long timeout;

    if (RedisModule_StringToLongLong(argv[1],&delay) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    if (RedisModule_StringToLongLong(argv[2],&timeout) != REDISMODULE_OK) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid count");
    }

    pthread_t tid;
    RedisModuleBlockedClient *bc = RedisModule_BlockClient(ctx,HelloBlock_Reply,HelloBlock_Timeout,HelloBlock_FreeData,timeout);

    /* Here we set a disconnection handler, however since this module will
     * block in sleep() in a thread, there is not much we can do in the
     * callback, so this is just to show you the API. */
    RedisModule_SetDisconnectCallback(bc,HelloBlock_Disconnected);

    /* Now that we setup a blocking client, we need to pass the control
     * to the thread. However we need to pass arguments to the thread:
     * the delay and a reference to the blocked client handle. */
    void **targ = RedisModule_Alloc(sizeof(void*)*2);
    targ[0] = bc;
    targ[1] = (void*)(unsigned long) delay;

    if (pthread_create(&tid,NULL,HelloBlock_ThreadMain,targ) != 0) {
        RedisModule_AbortBlock(bc);
        return RedisModule_ReplyWithError(ctx,"-ERR Can't start thread");
    }
    return REDISMODULE_OK;
}