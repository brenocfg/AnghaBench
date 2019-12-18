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
typedef  int /*<<< orphan*/  RedisModuleCallReply ;
typedef  int /*<<< orphan*/  RedisModuleBlockedClient ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_POSTPONED_ARRAY_LEN ; 
 int /*<<< orphan*/ * RedisModule_Call (int /*<<< orphan*/ *,char*,char*,long long) ; 
 int /*<<< orphan*/ * RedisModule_CallReplyArrayElement (int /*<<< orphan*/ *,size_t) ; 
 size_t RedisModule_CallReplyLength (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_CreateStringFromCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeCallReply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_FreeThreadSafeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_GetThreadSafeContext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplySetArrayLength (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithCallReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int /*<<< orphan*/  RedisModule_ThreadSafeContextLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ThreadSafeContextUnlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_UnblockClient (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void *HelloKeys_ThreadMain(void *arg) {
    RedisModuleBlockedClient *bc = arg;
    RedisModuleCtx *ctx = RedisModule_GetThreadSafeContext(bc);
    long long cursor = 0;
    size_t replylen = 0;

    RedisModule_ReplyWithArray(ctx,REDISMODULE_POSTPONED_ARRAY_LEN);
    do {
        RedisModule_ThreadSafeContextLock(ctx);
        RedisModuleCallReply *reply = RedisModule_Call(ctx,
            "SCAN","l",(long long)cursor);
        RedisModule_ThreadSafeContextUnlock(ctx);

        RedisModuleCallReply *cr_cursor =
            RedisModule_CallReplyArrayElement(reply,0);
        RedisModuleCallReply *cr_keys =
            RedisModule_CallReplyArrayElement(reply,1);

        RedisModuleString *s = RedisModule_CreateStringFromCallReply(cr_cursor);
        RedisModule_StringToLongLong(s,&cursor);
        RedisModule_FreeString(ctx,s);

        size_t items = RedisModule_CallReplyLength(cr_keys);
        for (size_t j = 0; j < items; j++) {
            RedisModuleCallReply *ele =
                RedisModule_CallReplyArrayElement(cr_keys,j);
            RedisModule_ReplyWithCallReply(ctx,ele);
            replylen++;
        }
        RedisModule_FreeCallReply(reply);
    } while (cursor != 0);
    RedisModule_ReplySetArrayLength(ctx,replylen);

    RedisModule_FreeThreadSafeContext(ctx);
    RedisModule_UnblockClient(bc,NULL);
    return NULL;
}