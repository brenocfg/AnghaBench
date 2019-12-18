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
 int /*<<< orphan*/  REDISMODULE_ERRORMSG_WRONGTYPE ; 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 int REDISMODULE_KEYTYPE_STRING ; 
 int REDISMODULE_OK ; 
 int REDISMODULE_READ ; 
 int REDISMODULE_WRITE ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplicateVerbatim (int /*<<< orphan*/ *) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithSimpleString (int /*<<< orphan*/ *,char*) ; 
 char* RedisModule_StringDMA (int /*<<< orphan*/ *,size_t*,int) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 scalar_t__ isupper (char) ; 
 char tolower (char) ; 
 char toupper (char) ; 

int HelloToggleCase_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 2) return RedisModule_WrongArity(ctx);

    RedisModuleKey *key = RedisModule_OpenKey(ctx,argv[1],
        REDISMODULE_READ|REDISMODULE_WRITE);

    int keytype = RedisModule_KeyType(key);
    if (keytype != REDISMODULE_KEYTYPE_STRING &&
        keytype != REDISMODULE_KEYTYPE_EMPTY)
    {
        RedisModule_CloseKey(key);
        return RedisModule_ReplyWithError(ctx,REDISMODULE_ERRORMSG_WRONGTYPE);
    }

    if (keytype == REDISMODULE_KEYTYPE_STRING) {
        size_t len, j;
        char *s = RedisModule_StringDMA(key,&len,REDISMODULE_WRITE);
        for (j = 0; j < len; j++) {
            if (isupper(s[j])) {
                s[j] = tolower(s[j]);
            } else {
                s[j] = toupper(s[j]);
            }
        }
    }

    RedisModule_CloseKey(key);
    RedisModule_ReplyWithSimpleString(ctx,"OK");
    RedisModule_ReplicateVerbatim(ctx);
    return REDISMODULE_OK;
}