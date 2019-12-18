#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  listNode ;
struct TYPE_10__ {TYPE_1__* module; } ;
struct TYPE_9__ {TYPE_1__* module; } ;
struct TYPE_8__ {int /*<<< orphan*/  filters; } ;
typedef  TYPE_2__ RedisModuleCtx ;
typedef  TYPE_3__ RedisModuleCommandFilter ;

/* Variables and functions */
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 int /*<<< orphan*/  listDelNode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  moduleCommandFilters ; 
 int /*<<< orphan*/  zfree (TYPE_3__*) ; 

int RM_UnregisterCommandFilter(RedisModuleCtx *ctx, RedisModuleCommandFilter *filter) {
    listNode *ln;

    /* A module can only remove its own filters */
    if (filter->module != ctx->module) return REDISMODULE_ERR;

    ln = listSearchKey(moduleCommandFilters,filter);
    if (!ln) return REDISMODULE_ERR;
    listDelNode(moduleCommandFilters,ln);

    ln = listSearchKey(ctx->module->filters,filter);
    if (!ln) return REDISMODULE_ERR;    /* Shouldn't happen */
    listDelNode(ctx->module->filters,ln);

    zfree(filter);

    return REDISMODULE_OK;
}