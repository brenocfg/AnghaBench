#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sds ;
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_8__ {TYPE_2__* value; } ;
typedef  TYPE_1__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_9__ {char* ip; int port; int /*<<< orphan*/  context; } ;
typedef  TYPE_2__ clusterManagerNode ;
struct TYPE_10__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 char* CLUSTER_MANAGER_INVALID_HOST_ARG ; 
 int REDIS_OK ; 
 scalar_t__ cliFormatReplyRaw (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clusterManagerLoadInfoFromNode (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clusterManagerLogInfo (char*) ; 
 TYPE_2__* clusterManagerNewNode (char*,int) ; 
 int /*<<< orphan*/  clusterManagerNodeConnect (TYPE_2__*) ; 
 TYPE_4__ cluster_manager ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getClusterHostFromCmdArgs (int,char**,char**,int*) ; 
 TYPE_1__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  redisAppendCommandArgv (int /*<<< orphan*/ ,int,char const**,size_t*) ; 
 int redisGetReply (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  sdsfree (scalar_t__) ; 
 int /*<<< orphan*/  stderr ; 
 size_t strlen (char*) ; 
 int /*<<< orphan*/  zfree (size_t*) ; 
 size_t* zmalloc (int) ; 

__attribute__((used)) static int clusterManagerCommandCall(int argc, char **argv) {
    int port = 0, i;
    char *ip = NULL;
    if (!getClusterHostFromCmdArgs(1, argv, &ip, &port)) goto invalid_args;
    clusterManagerNode *refnode = clusterManagerNewNode(ip, port);
    if (!clusterManagerLoadInfoFromNode(refnode, 0)) return 0;
    argc--;
    argv++;
    size_t *argvlen = zmalloc(argc*sizeof(size_t));
    clusterManagerLogInfo(">>> Calling");
    for (i = 0; i < argc; i++) {
        argvlen[i] = strlen(argv[i]);
        printf(" %s", argv[i]);
    }
    printf("\n");
    listIter li;
    listNode *ln;
    listRewind(cluster_manager.nodes, &li);
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (!n->context && !clusterManagerNodeConnect(n)) continue;
        redisReply *reply = NULL;
        redisAppendCommandArgv(n->context, argc, (const char **) argv, argvlen);
        int status = redisGetReply(n->context, (void **)(&reply));
        if (status != REDIS_OK || reply == NULL )
            printf("%s:%d: Failed!\n", n->ip, n->port);
        else {
            sds formatted_reply = cliFormatReplyRaw(reply);
            printf("%s:%d: %s\n", n->ip, n->port, (char *) formatted_reply);
            sdsfree(formatted_reply);
        }
        if (reply != NULL) freeReplyObject(reply);
    }
    zfree(argvlen);
    return 1;
invalid_args:
    fprintf(stderr, CLUSTER_MANAGER_INVALID_HOST_ARG);
    return 0;
}