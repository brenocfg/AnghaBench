#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int in_dict_field; TYPE_1__* module; int /*<<< orphan*/  info; int /*<<< orphan*/  in_section; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RedisModuleInfoCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RM_InfoEndDictField (TYPE_2__*) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*) ; 

int RM_InfoBeginDictField(RedisModuleInfoCtx *ctx, char *name) {
    if (!ctx->in_section)
        return REDISMODULE_ERR;
    /* Implicitly end dicts, instead of returning an error which is likely un checked. */
    if (ctx->in_dict_field)
        RM_InfoEndDictField(ctx);
    ctx->info = sdscatfmt(ctx->info,
        "%s_%s:",
        ctx->module->name,
        name);
    ctx->in_dict_field = 1;
    return REDISMODULE_OK;
}