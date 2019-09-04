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
 int /*<<< orphan*/  HelloHCopy_RedisCommand ; 
 int /*<<< orphan*/  HelloLeftPad_RedisCommand ; 
 int /*<<< orphan*/  HelloLexRange_RedisCommand ; 
 int /*<<< orphan*/  HelloListSpliceAuto_RedisCommand ; 
 int /*<<< orphan*/  HelloListSplice_RedisCommand ; 
 int /*<<< orphan*/  HelloListSumLen_RedisCommand ; 
 int /*<<< orphan*/  HelloMoreExpire_RedisCommand ; 
 int /*<<< orphan*/  HelloPushCall2_RedisCommand ; 
 int /*<<< orphan*/  HelloPushCall_RedisCommand ; 
 int /*<<< orphan*/  HelloPushNative_RedisCommand ; 
 int /*<<< orphan*/  HelloRandArray_RedisCommand ; 
 int /*<<< orphan*/  HelloRepl1_RedisCommand ; 
 int /*<<< orphan*/  HelloRepl2_RedisCommand ; 
 int /*<<< orphan*/  HelloSimple_RedisCommand ; 
 int /*<<< orphan*/  HelloToggleCase_RedisCommand ; 
 int /*<<< orphan*/  HelloZsumRange_RedisCommand ; 
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 scalar_t__ REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int,int,int) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 char* RedisModule_StringPtrLen (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int,char const*) ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (RedisModule_Init(ctx,"helloworld",1,REDISMODULE_APIVER_1)
        == REDISMODULE_ERR) return REDISMODULE_ERR;

    /* Log the list of parameters passing loading the module. */
    for (int j = 0; j < argc; j++) {
        const char *s = RedisModule_StringPtrLen(argv[j],NULL);
        printf("Module loaded with ARGV[%d] = %s\n", j, s);
    }

    if (RedisModule_CreateCommand(ctx,"hello.simple",
        HelloSimple_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.push.native",
        HelloPushNative_RedisCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.push.call",
        HelloPushCall_RedisCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.push.call2",
        HelloPushCall2_RedisCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.list.sum.len",
        HelloListSumLen_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.list.splice",
        HelloListSplice_RedisCommand,"write deny-oom",1,2,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.list.splice.auto",
        HelloListSpliceAuto_RedisCommand,
        "write deny-oom",1,2,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.rand.array",
        HelloRandArray_RedisCommand,"readonly",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.repl1",
        HelloRepl1_RedisCommand,"write",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.repl2",
        HelloRepl2_RedisCommand,"write",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.toggle.case",
        HelloToggleCase_RedisCommand,"write",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.more.expire",
        HelloMoreExpire_RedisCommand,"write",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.zsumrange",
        HelloZsumRange_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.lexrange",
        HelloLexRange_RedisCommand,"readonly",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.hcopy",
        HelloHCopy_RedisCommand,"write deny-oom",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"hello.leftpad",
        HelloLeftPad_RedisCommand,"",1,1,1) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}