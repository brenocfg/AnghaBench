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
struct TYPE_2__ {scalar_t__ cluster_enabled; } ;
typedef  int /*<<< orphan*/  RedisModuleString ;
typedef  int /*<<< orphan*/  RedisModuleCtx ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterPropagatePublish (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int pubsubPublishMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__ server ; 

int RM_PublishMessage(RedisModuleCtx *ctx, RedisModuleString *channel, RedisModuleString *message) {
    UNUSED(ctx);
    int receivers = pubsubPublishMessage(channel, message);
    if (server.cluster_enabled)
        clusterPropagatePublish(channel, message);
    return receivers;
}