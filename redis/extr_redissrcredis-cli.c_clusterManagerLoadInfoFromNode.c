#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_15__ {int flags; int /*<<< orphan*/  replicas_count; int /*<<< orphan*/ * replicate; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/ * friends; int /*<<< orphan*/ * context; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_16__ {int /*<<< orphan*/ * nodes; } ;

/* Variables and functions */
 int CLUSTER_MANAGER_FLAG_DISCONNECT ; 
 int CLUSTER_MANAGER_FLAG_FAIL ; 
 int CLUSTER_MANAGER_FLAG_NOADDR ; 
 int CLUSTER_MANAGER_OPT_GETFRIENDS ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogWarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* clusterManagerNodeByName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterManagerNodeConnect (TYPE_2__*) ; 
 int /*<<< orphan*/  clusterManagerNodeIsCluster (TYPE_2__*,char**) ; 
 scalar_t__ clusterManagerNodeLoadInfo (TYPE_2__*,int,char**) ; 
 int /*<<< orphan*/  clusterManagerPrintNotClusterNodeError (TYPE_2__*,char*) ; 
 TYPE_6__ cluster_manager ; 
 int /*<<< orphan*/  freeClusterManagerNode (TYPE_2__*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (char*) ; 

__attribute__((used)) static int clusterManagerLoadInfoFromNode(clusterManagerNode *node, int opts) {
    if (node->context == NULL && !clusterManagerNodeConnect(node)) {
        freeClusterManagerNode(node);
        return 0;
    }
    opts |= CLUSTER_MANAGER_OPT_GETFRIENDS;
    char *e = NULL;
    if (!clusterManagerNodeIsCluster(node, &e)) {
        clusterManagerPrintNotClusterNodeError(node, e);
        if (e) zfree(e);
        freeClusterManagerNode(node);
        return 0;
    }
    e = NULL;
    if (!clusterManagerNodeLoadInfo(node, opts, &e)) {
        if (e) {
            CLUSTER_MANAGER_PRINT_REPLY_ERROR(node, e);
            zfree(e);
        }
        freeClusterManagerNode(node);
        return 0;
    }
    listIter li;
    listNode *ln;
    if (cluster_manager.nodes != NULL) {
        listRewind(cluster_manager.nodes, &li);
        while ((ln = listNext(&li)) != NULL)
            freeClusterManagerNode((clusterManagerNode *) ln->value);
        listRelease(cluster_manager.nodes);
    }
    cluster_manager.nodes = listCreate();
    listAddNodeTail(cluster_manager.nodes, node);
    if (node->friends != NULL) {
        listRewind(node->friends, &li);
        while ((ln = listNext(&li)) != NULL) {
            clusterManagerNode *friend = ln->value;
            if (!friend->ip || !friend->port) goto invalid_friend;
            if (!friend->context && !clusterManagerNodeConnect(friend))
                goto invalid_friend;
            e = NULL;
            if (clusterManagerNodeLoadInfo(friend, 0, &e)) {
                if (friend->flags & (CLUSTER_MANAGER_FLAG_NOADDR |
                                     CLUSTER_MANAGER_FLAG_DISCONNECT |
                                     CLUSTER_MANAGER_FLAG_FAIL))
                    goto invalid_friend;
                listAddNodeTail(cluster_manager.nodes, friend);
            } else {
                clusterManagerLogErr("[ERR] Unable to load info for "
                                     "node %s:%d\n",
                                     friend->ip, friend->port);
                goto invalid_friend;
            }
            continue;
invalid_friend:
            freeClusterManagerNode(friend);
        }
        listRelease(node->friends);
        node->friends = NULL;
    }
    // Count replicas for each node
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n->replicate != NULL) {
            clusterManagerNode *master = clusterManagerNodeByName(n->replicate);
            if (master == NULL) {
                clusterManagerLogWarn("*** WARNING: %s:%d claims to be "
                                      "slave of unknown node ID %s.\n",
                                      n->ip, n->port, n->replicate);
            } else master->replicas_count++;
        }
    }
    return 1;
}