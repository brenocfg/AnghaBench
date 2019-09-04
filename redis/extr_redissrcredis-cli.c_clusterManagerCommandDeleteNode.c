#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_11__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_12__ {scalar_t__ slots_count; char* name; int /*<<< orphan*/  context; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; scalar_t__ replicate; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_13__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CLUSTER_MANAGER_COMMAND (TYPE_2__*,char*,char*) ; 
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int clusterManagerCheckRedisReply (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*,...) ; 
 TYPE_2__* clusterManagerNewNode (char*,int) ; 
 TYPE_2__* clusterManagerNodeByName (char*) ; 
 TYPE_2__* clusterManagerNodeWithLeastReplicas () ; 
 TYPE_4__ cluster_manager ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisCommand (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcasecmp (scalar_t__,char*) ; 

__attribute__((used)) static int clusterManagerCommandDeleteNode(int argc, char **argv) {
    UNUSED(argc);
    int success = 1;
    int port = 0;
    char *ip = NULL;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port)) goto invalid_args;
    char *node_id = argv[1];
    clusterManagerLogInfo(">>> Removing node %s from cluster %s:%d\n",
                          node_id, ip, port);
    clusterManagerNode *ref_node = clusterManagerNewNode(ip, port);
    clusterManagerNode *node = NULL;

    // Load cluster information
    if (!clusterManagerLoadInfoFromNode(ref_node, 0)) return 0;

    // Check if the node exists and is not empty
    node = clusterManagerNodeByName(node_id);
    if (node == NULL) {
        clusterManagerLogErr("[ERR] No such node ID %s\n", node_id);
        return 0;
    }
    if (node->slots_count != 0) {
        clusterManagerLogErr("[ERR] Node %s:%d is not empty! Reshard data "
                             "away and try again.\n", node->ip, node->port);
        return 0;
    }

    // Send CLUSTER FORGET to all the nodes but the node to remove
    clusterManagerLogInfo(">>> Sending CLUSTER FORGET messages to the "
                          "cluster...\n");
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n == node) continue;
        if (n->replicate && !strcasecmp(n->replicate, node_id)) {
            // Reconfigure the slave to replicate with some other node
            clusterManagerNode *master = clusterManagerNodeWithLeastReplicas();
            assert(master != NULL);
            clusterManagerLogInfo(">>> %s:%d as replica of %s:%d\n",
                                  n->ip, n->port, master->ip, master->port);
            redisReply *r = CLUSTER_MANAGER_COMMAND(n, "CLUSTER REPLICATE %s",
                                                    master->name);
            success = clusterManagerCheckRedisReply(n, r, NULL);
            if (r) freeReplyObject(r);
            if (!success) return 0;
        }
        redisReply *r = CLUSTER_MANAGER_COMMAND(n, "CLUSTER FORGET %s",
                                                node_id);
        success = clusterManagerCheckRedisReply(n, r, NULL);
        if (r) freeReplyObject(r);
        if (!success) return 0;
    }

    /* Finally send CLUSTER RESET to the node. */
    clusterManagerLogInfo(">>> Sending CLUSTER RESET SOFT to the "
                          "deleted node.\n");
    redisReply *r = redisCommand(node->context, "CLUSTER RESET %s", "SOFT");
    success = clusterManagerCheckRedisReply(node, r, NULL);
    if (r) freeReplyObject(r);
    return success;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}