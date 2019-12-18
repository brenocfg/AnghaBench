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
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_AutoMemory (int /*<<< orphan*/ *) ; 
 char* RedisModule_PoolAlloc (int /*<<< orphan*/ *,long long) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int RedisModule_ReplyWithString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithStringBuffer (int /*<<< orphan*/ *,char*,long long) ; 
 char* RedisModule_StringPtrLen (int /*<<< orphan*/ *,size_t*) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 

int HelloLeftPad_RedisCommand(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    RedisModule_AutoMemory(ctx); /* Use automatic memory management. */
    long long padlen;

    if (argc != 4) return RedisModule_WrongArity(ctx);

    if ((RedisModule_StringToLongLong(argv[2],&padlen) != REDISMODULE_OK) ||
        (padlen< 0)) {
        return RedisModule_ReplyWithError(ctx,"ERR invalid padding length");
    }
    size_t strlen, chlen;
    const char *str = RedisModule_StringPtrLen(argv[1], &strlen);
    const char *ch = RedisModule_StringPtrLen(argv[3], &chlen);

    /* If the string is already larger than the target len, just return
     * the string itself. */
    if (strlen >= (size_t)padlen)
        return RedisModule_ReplyWithString(ctx,argv[1]);

    /* Padding must be a single character in this simple implementation. */
    if (chlen != 1)
        return RedisModule_ReplyWithError(ctx,
            "ERR padding must be a single char");

    /* Here we use our pool allocator, for our throw-away allocation. */
    padlen -= strlen;
    char *buf = RedisModule_PoolAlloc(ctx,padlen+strlen);
    for (long long j = 0; j < padlen; j++) buf[j] = *ch;
    memcpy(buf+padlen,str,strlen);

    RedisModule_ReplyWithStringBuffer(ctx,buf,padlen+strlen);
    return REDISMODULE_OK;
}