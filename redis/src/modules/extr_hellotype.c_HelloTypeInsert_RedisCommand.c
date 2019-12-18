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
struct HelloTypeObject {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleKey ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 scalar_t__ HelloType ; 
 int /*<<< orphan*/  HelloTypeInsert (struct HelloTypeObject*,long long) ; 
 char* REDISMODULE_ERRORMSG_WRONGTYPE ; 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 scalar_t__ REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_ModuleTypeGetType (int /*<<< orphan*/ *) ; 
 struct HelloTypeObject* RedisModule_ModuleTypeGetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ModuleTypeSetValue (int /*<<< orphan*/ *,scalar_t__,struct HelloTypeObject*) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplicateVerbatim (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_SignalKeyAsReady (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 struct HelloTypeObject* createHelloTypeObject () ; 

int HelloTypeInsert_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */

    if (argc != 3) return RedisModule_WrongArity(ctx);
    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);
    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY &&
        RedisModule_ModuleTypeGetType(key) != HelloType)
    {
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    long long value;
    if ((RedisModule_StringToLongLong(argv[2],&value) != REDISMODULE_OK)) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid value: must be a signed 64 bit integer");
    }

    /* Create an empty value object if the key is currently empty. */
    struct HelloTypeObject *hto;
    if (type == REDISMODULE_KEYTYPE_EMPTY) {
        hto = createHelloTypeObject();
        RedisModule_ModuleTypeSetValue(key,HelloType,hto);
    } else {
        hto = RedisModule_ModuleTypeGetValue(key);
    }

    /* Insert the new element. */
    HelloTypeInsert(hto,value);
    RedisModule_SignalKeyAsReady(ctx,argv[1]);

    RedisModule_ReplyWithLongLong(ctx,hto->len);
    RedisModule_ReplicateVerbatim(ctx);
    return REDISMODULE_OK;
}