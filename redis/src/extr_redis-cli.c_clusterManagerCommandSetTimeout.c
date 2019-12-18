#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_9__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_10__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_11__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/ * CLUSTER_MANAGER_COMMAND (TYPE_2__*,char*,char*,...) ; 
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int atoi (char*) ; 
 int clusterManagerCheckRedisReply (TYPE_2__*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogWarn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* clusterManagerNewNode (char*,int) ; 
 TYPE_4__ cluster_manager ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  zfree (char*) ; 

__attribute__((used)) static int clusterManagerCommandSetTimeout(int argc, char **argv) {
    UNUSED(argc);
    int port = 0;
    char *ip = NULL;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port)) goto invalid_args;
    int timeout = atoi(argv[1]);
    if (timeout < 100) {
        fprintf(stderr, "Setting a node timeout of less than 100 "
                "milliseconds is a bad idea.\n");
        return 0;
    }
    // Load cluster information
    clusterManagerNode *node = clusterManagerNewNode(ip, port);
    if (!clusterManagerLoadInfoFromNode(node, 0)) return 0;
    int ok_count = 0, err_count = 0;

    clusterManagerLogInfo(">>> Reconfiguring node timeout in every "
                          "cluster node...\n");
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        char *err = NULL;
        redisReply *reply = CLUSTER_MANAGER_COMMAND(n, "CONFIG %s %s %d",
                                                    "SET",
                                                    "cluster-node-timeout",
                                                    timeout);
        if (reply == NULL) goto reply_err;
        int ok = clusterManagerCheckRedisReply(n, reply, &err);
        freeReplyObject(reply);
        if (!ok) goto reply_err;
        reply = CLUSTER_MANAGER_COMMAND(n, "CONFIG %s", "REWRITE");
        if (reply == NULL) goto reply_err;
        ok = clusterManagerCheckRedisReply(n, reply, &err);
        freeReplyObject(reply);
        if (!ok) goto reply_err;
        clusterManagerLogWarn("*** New timeout set for %s:%d\n", n->ip,
                              n->port);
        ok_count++;
        continue;
reply_err:;
        int need_free = 0;
        if (err == NULL) err = "";
        else need_free = 1;
        clusterManagerLogErr("ERR setting node-timeot for %s:%d: %s\n", n->ip,
                             n->port, err);
        if (need_free) zfree(err);
        err_count++;
    }
    clusterManagerLogInfo(">>> New node timeout set. %d OK, %d ERR.\n",
                          ok_count, err_count);
    return 1;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}