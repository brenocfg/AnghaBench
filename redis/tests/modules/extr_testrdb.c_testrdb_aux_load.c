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
typedef  int /*<<< orphan*/  RedisModuleIO ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int REDISMODULE_AUX_AFTER_RDB ; 
 int REDISMODULE_AUX_BEFORE_RDB ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RedisModule_FreeString (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_GetContextFromIO (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_IsIOError (int /*<<< orphan*/ *) ; 
 int RedisModule_LoadSigned (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_LoadString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * after_str ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * before_str ; 
 int conf_aux_count ; 

int testrdb_aux_load(RedisModuleIO *rdb, int encver, int when) {
    assert(encver == 1);
    if (conf_aux_count==1) assert(when == REDISMODULE_AUX_AFTER_RDB);
    if (conf_aux_count==0) assert(0);
    RedisModuleCtx *ctx = RedisModule_GetContextFromIO(rdb);
    if (when == REDISMODULE_AUX_BEFORE_RDB) {
        if (before_str)
            RedisModule_FreeString(ctx, before_str);
        before_str = NULL;
        int count = RedisModule_LoadSigned(rdb);
        if (RedisModule_IsIOError(rdb))
            return REDISMODULE_ERR;
        if (count)
            before_str = RedisModule_LoadString(rdb);
    } else {
        if (after_str)
            RedisModule_FreeString(ctx, after_str);
        after_str = NULL;
        int count = RedisModule_LoadSigned(rdb);
        if (RedisModule_IsIOError(rdb))
            return REDISMODULE_ERR;
        if (count)
            after_str = RedisModule_LoadString(rdb);
    }
    if (RedisModule_IsIOError(rdb))
        return REDISMODULE_ERR;
    return REDISMODULE_OK;
}