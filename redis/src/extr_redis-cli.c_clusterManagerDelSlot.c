#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int clusterManagerCheckRedisReply (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 int /*<<< orphan*/ * clusterManagerGetSlotOwner (int /*<<< orphan*/ *,int,char**) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (char*) ; 

__attribute__((used)) static int clusterManagerDelSlot(clusterManagerNode *node, int slot,
                                 int ignore_unassigned_err)
{
    redisReply *reply = CLUSTER_MANAGER_COMMAND(node,
        "CLUSTER DELSLOTS %d", slot);
    char *err = NULL;
    int success = clusterManagerCheckRedisReply(node, reply, &err);
    if (!success && reply && reply->type == REDIS_REPLY_ERROR &&
        ignore_unassigned_err)
    {
        char *get_owner_err = NULL;
        clusterManagerNode *assigned_to =
            clusterManagerGetSlotOwner(node, slot, &get_owner_err);
        if (!assigned_to) {
            if (get_owner_err == NULL) success = 1;
            else {
                CLUSTER_MANAGER_PRINT_REPLY_ERROR(node, get_owner_err);
                zfree(get_owner_err);
            }
        }
    }
    if (!success && err != NULL) {
        CLUSTER_MANAGER_PRINT_REPLY_ERROR(node, err);
        zfree(err);
    }
    if (reply) freeReplyObject(reply);
    return success;
}