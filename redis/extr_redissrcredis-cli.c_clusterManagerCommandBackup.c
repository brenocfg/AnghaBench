#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  char* sds ;
struct TYPE_12__ {TYPE_3__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_13__ {int /*<<< orphan*/  port; int /*<<< orphan*/  ip; scalar_t__ replicate; } ;
typedef  TYPE_3__ clusterManagerNode ;
struct TYPE_15__ {int /*<<< orphan*/  nodes; int /*<<< orphan*/  errors; } ;
struct TYPE_11__ {char* backup_dir; } ;
struct TYPE_14__ {TYPE_1__ cluster_manager_command; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int /*<<< orphan*/  UNUSED (int) ; 
 int clusterManagerCheckCluster (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogErr (char*,char*) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*,char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogOk (char*,...) ; 
 int /*<<< orphan*/  clusterManagerLogWarn (char*) ; 
 TYPE_3__* clusterManagerNewNode (char*,int) ; 
 char* clusterManagerNodeGetJSON (TYPE_3__*,int) ; 
 TYPE_7__ cluster_manager ; 
 TYPE_6__ config ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 int /*<<< orphan*/  getRDB (TYPE_3__*) ; 
 int listLength (int /*<<< orphan*/ ) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* sdscat (char*,char*) ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int sdslen (char*) ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static int clusterManagerCommandBackup(int argc, char **argv) {
    UNUSED(argc);
    int success = 1, port = 0;
    char *ip = NULL;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port)) goto invalid_args;
    clusterManagerNode *refnode = clusterManagerNewNode(ip, port);
    if (!clusterManagerLoadInfoFromNode(refnode, 0)) return 0;
    int no_issues = clusterManagerCheckCluster(0);
    int cluster_errors_count = (no_issues ? 0 :
                                listLength(cluster_manager.errors));
    config.cluster_manager_command.backup_dir = argv[1];
    /* TODO: check if backup_dir is a valid directory. */
    sds json = sdsnew("[\n");
    int first_node = 0;
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        if (!first_node) first_node = 1;
        else json = sdscat(json, ",\n");
        clusterManagerNode *node = ln->value;
        sds node_json = clusterManagerNodeGetJSON(node, cluster_errors_count);
        json = sdscat(json, node_json);
        sdsfree(node_json);
        if (node->replicate)
            continue;
        clusterManagerLogInfo(">>> Node %s:%d -> Saving RDB...\n",
                              node->ip, node->port);
        fflush(stdout);
        getRDB(node);
    }
    json = sdscat(json, "\n]");
    sds jsonpath = sdsnew(config.cluster_manager_command.backup_dir);
    if (jsonpath[sdslen(jsonpath) - 1] != '/')
        jsonpath = sdscat(jsonpath, "/");
    jsonpath = sdscat(jsonpath, "nodes.json");
    fflush(stdout);
    clusterManagerLogInfo("Saving cluster configuration to: %s\n", jsonpath);
    FILE *out = fopen(jsonpath, "w+");
    if (!out) {
        clusterManagerLogErr("Could not save nodes to: %s\n", jsonpath);
        success = 0;
        goto cleanup;
    }
    fputs(json, out);
    fclose(out);
cleanup:
    sdsfree(json);
    sdsfree(jsonpath);
    if (success) {
        if (!no_issues) {
            clusterManagerLogWarn("*** Cluster seems to have some problems, "
                                  "please be aware of it if you're going "
                                  "to restore this backup.\n");
        }
        clusterManagerLogOk("[OK] Backup created into: %s\n",
                            config.cluster_manager_command.backup_dir);
    } else clusterManagerLogOk("[ERR] Failed to back cluster!\n");
    return success;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}