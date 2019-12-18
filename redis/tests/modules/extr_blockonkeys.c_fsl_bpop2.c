#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int length; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ fsl_t ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 scalar_t__ REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_READ ; 
 int /*<<< orphan*/  RedisModule_BlockClientOnKeys (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,long long,int /*<<< orphan*/ **,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithArray (int /*<<< orphan*/ *,int) ; 
 int RedisModule_ReplyWithError (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ RedisModule_StringToLongLong (int /*<<< orphan*/ *,long long*) ; 
 int RedisModule_WrongArity (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpop2_reply_callback ; 
 int /*<<< orphan*/  bpop2_timeout_callback ; 
 int /*<<< orphan*/  get_fsl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int) ; 

int fsl_bpop2(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    if (argc != 3)
        return RedisModule_WrongArity(ctx);

    long long timeout;
    if (RedisModule_StringToLongLong(argv[2],&timeout) != REDISMODULE_OK || timeout < 0)
        return RedisModule_ReplyWithError(ctx,"ERR invalid timeout");

    fsl_t *fsl;
    if (!get_fsl(ctx, argv[1], REDISMODULE_READ, 0, &fsl, 1))
        return REDISMODULE_OK;

    if (!fsl || fsl->length < 2) {
        /* Key is empty or has <2 elements, we must block */
        RedisModule_BlockClientOnKeys(ctx, bpop2_reply_callback, bpop2_timeout_callback,
                                      NULL, timeout, &argv[1], 1, NULL);
    } else {
        RedisModule_ReplyWithArray(ctx, 2);
        RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
        RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    }

    return REDISMODULE_OK;
}