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
typedef  int /*<<< orphan*/  fsl_t ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleKey ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_ERRORMSG_WRONGTYPE ; 
 int REDISMODULE_KEYTYPE_EMPTY ; 
 int /*<<< orphan*/  RedisModule_CloseKey (int /*<<< orphan*/ *) ; 
 int RedisModule_KeyType (int /*<<< orphan*/ *) ; 
 scalar_t__ RedisModule_ModuleTypeGetType (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_ModuleTypeGetValue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RedisModule_ModuleTypeSetValue (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * RedisModule_OpenKey (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  RedisModule_ReplyWithError (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fsl_type_create () ; 
 scalar_t__ fsltype ; 

int get_fsl(RedisModuleCtx *ctx, RedisModuleString *keyname, int mode, int create, fsl_t **fsl, int reply_on_failure) {
    RedisModuleKey *key = RedisModule_OpenKey(ctx, keyname, mode);

    int type = RedisModule_KeyType(key);
    if (type != REDISMODULE_KEYTYPE_EMPTY && RedisModule_ModuleTypeGetType(key) != fsltype) {
        RedisModule_CloseKey(key);
        if (reply_on_failure)
            RedisModule_ReplyWithError(ctx, REDISMODULE_ERRORMSG_WRONGTYPE);
        return 0;
    }

    /* Create an empty value object if the key is currently empty. */
    if (type == REDISMODULE_KEYTYPE_EMPTY) {
        if (!create) {
            /* Key is empty but we cannot create */
            RedisModule_CloseKey(key);
            *fsl = NULL;
            return 1;
        }
        *fsl = fsl_type_create();
        RedisModule_ModuleTypeSetValue(key, fsltype, *fsl);
    } else {
        *fsl = RedisModule_ModuleTypeGetValue(key);
    }

    RedisModule_CloseKey(key);
    return 1;
}