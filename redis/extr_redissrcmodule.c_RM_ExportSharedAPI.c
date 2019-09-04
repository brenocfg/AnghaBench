#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sharedapi; } ;
struct TYPE_9__ {int /*<<< orphan*/  module; } ;
struct TYPE_8__ {void* func; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ RedisModuleSharedAPI ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 scalar_t__ DICT_OK ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ dictAdd (int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 TYPE_5__ server ; 
 int /*<<< orphan*/  zfree (TYPE_1__*) ; 
 TYPE_1__* zmalloc (int) ; 

int RM_ExportSharedAPI(RedisModuleCtx *ctx, const char *apiname, void *func) {
    RedisModuleSharedAPI *sapi = zmalloc(sizeof(*sapi));
    sapi->module = ctx->module;
    sapi->func = func;
    if (dictAdd(server.sharedapi, (char*)apiname, sapi) != DICT_OK) {
        zfree(sapi);
        return REDISMODULE_ERR;
    }
    return REDISMODULE_OK;
}