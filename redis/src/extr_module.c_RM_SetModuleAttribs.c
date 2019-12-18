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
struct TYPE_6__ {int ver; int apiver; scalar_t__ options; scalar_t__ in_hook; scalar_t__ in_call; void* filters; void* using; void* usedby; void* types; int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_2__* module; } ;
typedef  TYPE_1__ RedisModuleCtx ;
typedef  TYPE_2__ RedisModule ;

/* Variables and functions */
 void* listCreate () ; 
 int /*<<< orphan*/  sdsnew (char*) ; 
 TYPE_2__* zmalloc (int) ; 

void RM_SetModuleAttribs(RedisModuleCtx *ctx, const char *name, int ver, int apiver) {
    RedisModule *module;

    if (ctx->module != NULL) return;
    module = zmalloc(sizeof(*module));
    module->name = sdsnew((char*)name);
    module->ver = ver;
    module->apiver = apiver;
    module->types = listCreate();
    module->usedby = listCreate();
    module->using = listCreate();
    module->filters = listCreate();
    module->in_call = 0;
    module->in_hook = 0;
    module->options = 0;
    ctx->module = module;
}