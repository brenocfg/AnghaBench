#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dictEntry ;
struct TYPE_11__ {int /*<<< orphan*/  using; int /*<<< orphan*/  usedby; } ;
struct TYPE_10__ {int /*<<< orphan*/  sharedapi; } ;
struct TYPE_9__ {TYPE_4__* module; } ;
struct TYPE_8__ {void* func; TYPE_4__* module; } ;
typedef  TYPE_1__ RedisModuleSharedAPI ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/ * dictFind (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* dictGetVal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/ * listSearchKey (int /*<<< orphan*/ ,TYPE_4__*) ; 
 TYPE_3__ server ; 

void *RM_GetSharedAPI(RedisModuleCtx *ctx, const char *apiname) {
    dictEntry *de = dictFind(server.sharedapi, apiname);
    if (de == NULL) return NULL;
    RedisModuleSharedAPI *sapi = dictGetVal(de);
    if (listSearchKey(sapi->module->usedby,ctx->module) == NULL) {
        listAddNodeTail(sapi->module->usedby,ctx->module);
        listAddNodeTail(ctx->module->using,sapi->module);
    }
    return sapi->func;
}