#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  cluster_module_flags; } ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  CLUSTER_MODULE_FLAG_NO_FAILOVER ; 
 int /*<<< orphan*/  CLUSTER_MODULE_FLAG_NO_REDIRECTION ; 
 int REDISMODULE_CLUSTER_FLAG_NO_FAILOVER ; 
 int REDISMODULE_CLUSTER_FLAG_NO_REDIRECTION ; 
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

void RM_SetClusterFlags(RedisModuleCtx *ctx, uint64_t flags) {
    UNUSED(ctx);
    if (flags & REDISMODULE_CLUSTER_FLAG_NO_FAILOVER)
        server.cluster_module_flags |= CLUSTER_MODULE_FLAG_NO_FAILOVER;
    if (flags & REDISMODULE_CLUSTER_FLAG_NO_REDIRECTION)
        server.cluster_module_flags |= CLUSTER_MODULE_FLAG_NO_REDIRECTION;
}