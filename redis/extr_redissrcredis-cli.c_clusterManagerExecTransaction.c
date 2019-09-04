#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; size_t elements; struct TYPE_7__** element; } ;
typedef  TYPE_1__ redisReply ;
typedef  int (* clusterManagerOnReplyError ) (TYPE_1__*,int /*<<< orphan*/ *,size_t) ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ REDIS_REPLY_ARRAY ; 
 int clusterManagerCheckRedisReply (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  zfree (char*) ; 

__attribute__((used)) static int clusterManagerExecTransaction(clusterManagerNode *node,
                                         clusterManagerOnReplyError onerror)
{
    redisReply *reply = CLUSTER_MANAGER_COMMAND(node, "EXEC");
    int success = clusterManagerCheckRedisReply(node, reply, NULL);
    if (success) {
        if (reply->type != REDIS_REPLY_ARRAY) {
            success = 0;
            goto cleanup;
        }
        size_t i;
        for (i = 0; i < reply->elements; i++) {
            redisReply *r = reply->element[i];
            char *err = NULL;
            success = clusterManagerCheckRedisReply(node, r, &err);
            if (!success && onerror) success = onerror(r, node, i);
            if (err) {
                if (!success)
                    CLUSTER_MANAGER_PRINT_REPLY_ERROR(node, err);
                zfree(err);
            }
            if (!success) break;
        }
    }
cleanup:
    if (reply) freeReplyObject(reply);
    return success;
}