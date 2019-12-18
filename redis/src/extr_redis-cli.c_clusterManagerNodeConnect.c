#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  redisReply ;
struct TYPE_9__ {char* ip; int port; TYPE_2__* context; } ;
typedef  TYPE_1__ clusterManagerNode ;
struct TYPE_11__ {scalar_t__ auth; int /*<<< orphan*/ * user; scalar_t__ tls; } ;
struct TYPE_10__ {char* errstr; int /*<<< orphan*/  fd; scalar_t__ err; } ;

/* Variables and functions */
 int /*<<< orphan*/  REDIS_CLI_KEEPALIVE_INTERVAL ; 
 scalar_t__ REDIS_ERR ; 
 int /*<<< orphan*/  anetKeepAlive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ cliSecureConnection (TYPE_2__*,char const**) ; 
 int clusterManagerCheckRedisReply (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_5__ config ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeReplyObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * redisCommand (TYPE_2__*,char*,int /*<<< orphan*/ *,...) ; 
 TYPE_2__* redisConnect (char*,int) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int clusterManagerNodeConnect(clusterManagerNode *node) {
    if (node->context) redisFree(node->context);
    node->context = redisConnect(node->ip, node->port);
    if (!node->context->err && config.tls) {
        const char *err = NULL;
        if (cliSecureConnection(node->context, &err) == REDIS_ERR && err) {
            fprintf(stderr,"TLS Error: %s\n", err);
            redisFree(node->context);
            node->context = NULL;
            return 0;
        }
    }
    if (node->context->err) {
        fprintf(stderr,"Could not connect to Redis at ");
        fprintf(stderr,"%s:%d: %s\n", node->ip, node->port,
                node->context->errstr);
        redisFree(node->context);
        node->context = NULL;
        return 0;
    }
    /* Set aggressive KEEP_ALIVE socket option in the Redis context socket
     * in order to prevent timeouts caused by the execution of long
     * commands. At the same time this improves the detection of real
     * errors. */
    anetKeepAlive(NULL, node->context->fd, REDIS_CLI_KEEPALIVE_INTERVAL);
    if (config.auth) {
        redisReply *reply;
        if (config.user == NULL)
            reply = redisCommand(node->context,"AUTH %s", config.auth);
        else
            reply = redisCommand(node->context,"AUTH %s %s",
                                 config.user,config.auth);
        int ok = clusterManagerCheckRedisReply(node, reply, NULL);
        if (reply != NULL) freeReplyObject(reply);
        if (!ok) return 0;
    }
    return 1;
}