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
typedef  char* sds ;
struct TYPE_6__ {int in_section; char* info; int /*<<< orphan*/  sections; TYPE_1__* module; scalar_t__ requested_section; scalar_t__ in_dict_field; } ;
struct TYPE_5__ {char* name; } ;
typedef  TYPE_2__ RedisModuleInfoCtx ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  RM_InfoEndDictField (TYPE_2__*) ; 
 char* sdscat (char*,char*) ; 
 void* sdscatfmt (char*,char*,char*) ; 
 char* sdsdup (char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 scalar_t__ strcasecmp (scalar_t__,char*) ; 
 scalar_t__ strlen (char*) ; 

int RM_InfoAddSection(RedisModuleInfoCtx *ctx, char *name) {
    sds full_name = sdsdup(ctx->module->name);
    if (name != NULL && strlen(name) > 0)
        full_name = sdscatfmt(full_name, "_%s", name);

    /* Implicitly end dicts, instead of returning an error which is likely un checked. */
    if (ctx->in_dict_field)
        RM_InfoEndDictField(ctx);

    /* proceed only if:
     * 1) no section was requested (emit all)
     * 2) the module name was requested (emit all)
     * 3) this specific section was requested. */
    if (ctx->requested_section) {
        if (strcasecmp(ctx->requested_section, full_name) &&
            strcasecmp(ctx->requested_section, ctx->module->name)) {
            sdsfree(full_name);
            ctx->in_section = 0;
            return REDISMODULE_ERR;
        }
    }
    if (ctx->sections++) ctx->info = sdscat(ctx->info,"\r\n");
    ctx->info = sdscatfmt(ctx->info, "# %S\r\n", full_name);
    ctx->in_section = 1;
    sdsfree(full_name);
    return REDISMODULE_OK;
}