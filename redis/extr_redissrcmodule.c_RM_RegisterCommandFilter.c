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
struct TYPE_10__ {int flags; int /*<<< orphan*/  callback; TYPE_1__* module; } ;
struct TYPE_9__ {TYPE_1__* module; } ;
struct TYPE_8__ {int /*<<< orphan*/  filters; } ;
typedef  TYPE_2__ RedisModuleCtx ;
typedef  int /*<<< orphan*/  RedisModuleCommandFilterFunc ;
typedef  TYPE_3__ RedisModuleCommandFilter ;

/* Variables and functions */
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  moduleCommandFilters ; 
 TYPE_3__* zmalloc (int) ; 

RedisModuleCommandFilter *RM_RegisterCommandFilter(RedisModuleCtx *ctx, RedisModuleCommandFilterFunc callback, int flags) {
    RedisModuleCommandFilter *filter = zmalloc(sizeof(*filter));
    filter->module = ctx->module;
    filter->callback = callback;
    filter->flags = flags;

    listAddNodeTail(moduleCommandFilters, filter);
    listAddNodeTail(ctx->module->filters, filter);
    return filter;
}