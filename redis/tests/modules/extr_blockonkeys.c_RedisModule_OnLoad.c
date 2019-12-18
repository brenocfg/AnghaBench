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
struct TYPE_3__ {int /*<<< orphan*/ * digest; int /*<<< orphan*/  free; int /*<<< orphan*/ * mem_usage; int /*<<< orphan*/  aof_rewrite; int /*<<< orphan*/  rdb_save; int /*<<< orphan*/  rdb_load; int /*<<< orphan*/  version; } ;
typedef  TYPE_1__ RedisModuleTypeMethods ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  REDISMODULE_APIVER_1 ; 
 scalar_t__ REDISMODULE_ERR ; 
 int /*<<< orphan*/  REDISMODULE_NOT_USED (int) ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  REDISMODULE_TYPE_METHOD_VERSION ; 
 scalar_t__ RedisModule_CreateCommand (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * RedisModule_CreateDataType (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ RedisModule_Init (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsl_aofrw ; 
 int /*<<< orphan*/  fsl_bpop2 ; 
 int /*<<< orphan*/  fsl_bpopgt ; 
 int /*<<< orphan*/  fsl_free ; 
 int /*<<< orphan*/  fsl_push ; 
 int /*<<< orphan*/  fsl_rdb_load ; 
 int /*<<< orphan*/  fsl_rdb_save ; 
 int /*<<< orphan*/ * fsltype ; 

int RedisModule_OnLoad(RedisModuleCtx *ctx, RedisModuleString **argv, int argc) {
    REDISMODULE_NOT_USED(argv);
    REDISMODULE_NOT_USED(argc);

    if (RedisModule_Init(ctx, "blockonkeys", 1, REDISMODULE_APIVER_1)== REDISMODULE_ERR)
        return REDISMODULE_ERR;

    RedisModuleTypeMethods tm = {
        .version = REDISMODULE_TYPE_METHOD_VERSION,
        .rdb_load = fsl_rdb_load,
        .rdb_save = fsl_rdb_save,
        .aof_rewrite = fsl_aofrw,
        .mem_usage = NULL,
        .free = fsl_free,
        .digest = NULL
    };

    fsltype = RedisModule_CreateDataType(ctx, "fsltype_t", 0, &tm);
    if (fsltype == NULL)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"fsl.push",fsl_push,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"fsl.bpop2",fsl_bpop2,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    if (RedisModule_CreateCommand(ctx,"fsl.bpopgt",fsl_bpopgt,"",0,0,0) == REDISMODULE_ERR)
        return REDISMODULE_ERR;

    return REDISMODULE_OK;
}