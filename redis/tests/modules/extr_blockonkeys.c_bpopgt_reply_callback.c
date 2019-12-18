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
struct TYPE_3__ {long long* list; int length; } ;
typedef  TYPE_1__ fsl_t ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_READ ; 
 scalar_t__ RedisModule_GetBlockedClientPrivateData (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_GetBlockedClientReadyKey (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithLongLong (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  get_fsl (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ) ; 

int bpopgt_reply_callback(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);
    RedisModuleString *keyname = RedisModule_GetBlockedClientReadyKey(ctx);
    long long gt = (long long)RedisModule_GetBlockedClientPrivateData(ctx);

    fsl_t *fsl;
    if (!get_fsl(ctx, keyname, REDISMODULE_READ, 0, &fsl, 0))
        return REDISMODULE_ERR;

    if (!fsl || fsl->list[fsl->length-1] <= gt)
        return REDISMODULE_ERR;

    RedisModule_ReplyWithLongLong(ctx, fsl->list[--fsl->length]);
    return REDISMODULE_OK;
}