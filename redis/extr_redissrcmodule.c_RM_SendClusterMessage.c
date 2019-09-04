#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/  cluster_enabled; } ;
struct TYPE_6__ {TYPE_1__* module; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ RedisModuleCtx ;

/* Variables and functions */
 scalar_t__ C_OK ; 
 int REDISMODULE_ERR ; 
 int REDISMODULE_OK ; 
 scalar_t__ clusterSendModuleMessageToTarget (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  moduleTypeEncodeId (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__ server ; 

int RM_SendClusterMessage(RedisModuleCtx *ctx, char *target_id, uint8_t type, unsigned char *msg, uint32_t len) {
    if (!server.cluster_enabled) return REDISMODULE_ERR;
    uint64_t module_id = moduleTypeEncodeId(ctx->module->name,0);
    if (clusterSendModuleMessageToTarget(target_id,module_id,type,msg,len) == C_OK)
        return REDISMODULE_OK;
    else
        return REDISMODULE_ERR;
}