#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 int /*<<< orphan*/ * CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*) ; 
 int clusterManagerCheckRedisReply (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clusterManagerStartTransaction(clusterManagerNode *node) {
    redisReply *reply = CLUSTER_MANAGER_COMMAND(node, "MULTI");
    int success = clusterManagerCheckRedisReply(node, reply, NULL);
    if (reply) freeReplyObject(reply);
    return success;
}