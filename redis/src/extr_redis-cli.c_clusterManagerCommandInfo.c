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
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * clusterManagerNewNode (char*,int) ; 
 int /*<<< orphan*/  clusterManagerShowClusterInfo () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int clusterManagerCommandInfo(int argc, char **argv) {
    int port = 0;
    char *ip = NULL;
    if (!getClusterHostFromCmdArgs(argc, argv, &ip, &port)) goto invalid_args;
    clusterManagerNode *node = clusterManagerNewNode(ip, port);
    if (!clusterManagerLoadInfoFromNode(node, 0)) return 0;
    clusterManagerShowClusterInfo();
    return 1;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}