#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clusterManagerCheckRedisReply (int /*<<< orphan*/ *,TYPE_1__*,char**) ; 
 TYPE_1__* clusterManagerGetNodeRedisInfo (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 long getLongInfoField (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int clusterManagerNodeIsEmpty(clusterManagerNode *node, char **err) {
    redisReply *info = clusterManagerGetNodeRedisInfo(node, err);
    int is_empty = 1;
    if (info == NULL) return 0;
    if (strstr(info->str, "db0:") != NULL) {
        is_empty = 0;
        goto result;
    }
    freeReplyObject(info);
    info = CLUSTER_MANAGER_COMMAND(node, "CLUSTER INFO");
    if (err != NULL) *err = NULL;
    if (!clusterManagerCheckRedisReply(node, info, err)) {
        is_empty = 0;
        goto result;
    }
    long known_nodes = getLongInfoField(info->str, "cluster_known_nodes");
    is_empty = (known_nodes == 1);
result:
    freeReplyObject(info);
    return is_empty;
}