#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_22__ {char* ip; int port; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_25__ {int /*<<< orphan*/  nodes; } ;
struct TYPE_21__ {int flags; char* master_id; } ;
struct TYPE_24__ {TYPE_1__ cluster_manager_command; } ;
struct TYPE_23__ {TYPE_2__* value; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_CMD_FLAG_SLAVE ; 
 int /*<<< orphan*/ * CLUSTER_MANAGER_COMMAND (TYPE_2__*,char*,char*,...) ; 
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerCheckCluster (int /*<<< orphan*/ ) ; 
 int clusterManagerCheckRedisReply (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*,char*,int,...) ; 
 int /*<<< orphan*/  clusterManagerLogOk (char*) ; 
 TYPE_2__* clusterManagerNewNode (char*,int) ; 
 TYPE_2__* clusterManagerNodeByName (char*) ; 
 int /*<<< orphan*/  clusterManagerNodeConnect (TYPE_2__*) ; 
 int clusterManagerNodeIsCluster (TYPE_2__*,char**) ; 
 int clusterManagerNodeIsEmpty (TYPE_2__*,char**) ; 
 int /*<<< orphan*/  clusterManagerNodeLoadInfo (TYPE_2__*,int /*<<< orphan*/ ,char**) ; 
 TYPE_2__* clusterManagerNodeWithLeastReplicas () ; 
 int /*<<< orphan*/  clusterManagerPrintNotClusterNodeError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  clusterManagerPrintNotEmptyNodeError (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  clusterManagerWaitForClusterJoin () ; 
 TYPE_7__ cluster_manager ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeClusterManagerNode (TYPE_2__*) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_3__* listFirst (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zfree (char*) ; 

__attribute__((used)) static int clusterManagerCommandAddNode(int argc, char **argv) {
    int success = 1;
    redisReply *reply = NULL;
    char *ref_ip = NULL, *ip = NULL;
    int ref_port = 0, port = 0;
    if (!getClusterHostFromCmdArgs(argc - 1, argv + 1, &ref_ip, &ref_port))
        goto invalid_args;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port))
        goto invalid_args;
    clusterManagerLogInfo(">>> Adding node %s:%d to cluster %s:%d\n", ip, port,
                          ref_ip, ref_port);
    // Check the existing cluster
    clusterManagerNode *refnode = clusterManagerNewNode(ref_ip, ref_port);
    if (!clusterManagerLoadInfoFromNode(refnode, 0)) return 0;
    if (!clusterManagerCheckCluster(0)) return 0;

    /* If --cluster-master-id was specified, try to resolve it now so that we
     * abort before starting with the node configuration. */
    clusterManagerNode *master_node = NULL;
    if (config.cluster_manager_command.flags & CLUSTER_MANAGER_CMD_FLAG_SLAVE) {
        char *master_id = config.cluster_manager_command.master_id;
        if (master_id != NULL) {
            master_node = clusterManagerNodeByName(master_id);
            if (master_node == NULL) {
                clusterManagerLogErr("[ERR] No such master ID %s\n", master_id);
                return 0;
            }
        } else {
            master_node = clusterManagerNodeWithLeastReplicas();
            assert(master_node != NULL);
            printf("Automatically selected master %s:%d\n", master_node->ip,
                   master_node->port);
        }
    }

    // Add the new node
    clusterManagerNode *new_node = clusterManagerNewNode(ip, port);
    int added = 0;
    if (!clusterManagerNodeConnect(new_node)) {
        clusterManagerLogErr("[ERR] Sorry, can't connect to node %s:%d\n",
                             ip, port);
        success = 0;
        goto cleanup;
    }
    char *err = NULL;
    if (!(success = clusterManagerNodeIsCluster(new_node, &err))) {
        clusterManagerPrintNotClusterNodeError(new_node, err);
        if (err) zfree(err);
        goto cleanup;
    }
    if (!clusterManagerNodeLoadInfo(new_node, 0, &err)) {
        if (err) {
            CLUSTER_MANAGER_PRINT_REPLY_ERROR(new_node, err);
            zfree(err);
        }
        success = 0;
        goto cleanup;
    }
    if (!(success = clusterManagerNodeIsEmpty(new_node, &err))) {
        clusterManagerPrintNotEmptyNodeError(new_node, err);
        if (err) zfree(err);
        goto cleanup;
    }
    clusterManagerNode *first = listFirst(cluster_manager.nodes)->value;
    listAddNodeTail(cluster_manager.nodes, new_node);
    added = 1;

    // Send CLUSTER MEET command to the new node
    clusterManagerLogInfo(">>> Send CLUSTER MEET to node %s:%d to make it "
                          "join the cluster.\n", ip, port);
    reply = CLUSTER_MANAGER_COMMAND(new_node, "CLUSTER MEET %s %d",
                                    first->ip, first->port);
    if (!(success = clusterManagerCheckRedisReply(new_node, reply, NULL)))
        goto cleanup;

    /* Additional configuration is needed if the node is added as a slave. */
    if (master_node) {
        sleep(1);
        clusterManagerWaitForClusterJoin();
        clusterManagerLogInfo(">>> Configure node as replica of %s:%d.\n",
                              master_node->ip, master_node->port);
        freeReplyObject(reply);
        reply = CLUSTER_MANAGER_COMMAND(new_node, "CLUSTER REPLICATE %s",
                                        master_node->name);
        if (!(success = clusterManagerCheckRedisReply(new_node, reply, NULL)))
            goto cleanup;
    }
    clusterManagerLogOk("[OK] New node added correctly.\n");
cleanup:
    if (!added && new_node) freeClusterManagerNode(new_node);
    if (reply) freeReplyObject(reply);
    return success;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}