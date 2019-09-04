#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  void* sds ;
struct TYPE_14__ {scalar_t__ type; char* str; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_15__ {char* errstr; scalar_t__ err; } ;
typedef  TYPE_2__ redisContext ;
struct TYPE_16__ {char* ip; int port; char* name; int migrating_count; int importing_count; int* slots; scalar_t__ slots_count; void** importing; void** migrating; } ;
typedef  TYPE_3__ clusterNode ;
struct TYPE_13__ {char* hostsocket; char* hostip; int hostport; scalar_t__ cluster_nodes; } ;

/* Variables and functions */
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  addClusterNode (TYPE_3__*) ; 
 int atoi (char*) ; 
 TYPE_11__ config ; 
 TYPE_3__* createClusterNode (char*,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeClusterNodes () ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  printf (char*,char*,int) ; 
 TYPE_1__* redisCommand (TYPE_2__*,char*) ; 
 TYPE_2__* redisConnect (char*,int) ; 
 TYPE_2__* redisConnectUnix (char*) ; 
 int /*<<< orphan*/  redisFree (TYPE_2__*) ; 
 char* sdsnew (char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 
 void* zrealloc (void**,int) ; 

__attribute__((used)) static int fetchClusterConfiguration() {
    int success = 1;
    redisContext *ctx = NULL;
    redisReply *reply =  NULL;
    if (config.hostsocket == NULL)
        ctx = redisConnect(config.hostip,config.hostport);
    else
        ctx = redisConnectUnix(config.hostsocket);
    if (ctx->err) {
        fprintf(stderr,"Could not connect to Redis at ");
        if (config.hostsocket == NULL) {
            fprintf(stderr,"%s:%d: %s\n",config.hostip,config.hostport,
                    ctx->errstr);
        } else fprintf(stderr,"%s: %s\n",config.hostsocket,ctx->errstr);
        exit(1);
    }
    clusterNode *firstNode = createClusterNode((char *) config.hostip,
                                               config.hostport);
    if (!firstNode) {success = 0; goto cleanup;}
    reply = redisCommand(ctx, "CLUSTER NODES");
    success = (reply != NULL);
    if (!success) goto cleanup;
    success = (reply->type != REDIS_REPLY_ERROR);
    if (!success) {
        if (config.hostsocket == NULL) {
            fprintf(stderr, "Cluster node %s:%d replied with error:\n%s\n",
                    config.hostip, config.hostport, reply->str);
        } else {
            fprintf(stderr, "Cluster node %s replied with error:\n%s\n",
                    config.hostsocket, reply->str);
        }
        goto cleanup;
    }
    char *lines = reply->str, *p, *line;
    while ((p = strstr(lines, "\n")) != NULL) {
        *p = '\0';
        line = lines;
        lines = p + 1;
        char *name = NULL, *addr = NULL, *flags = NULL, *master_id = NULL;
        int i = 0;
        while ((p = strchr(line, ' ')) != NULL) {
            *p = '\0';
            char *token = line;
            line = p + 1;
            switch(i++){
            case 0: name = token; break;
            case 1: addr = token; break;
            case 2: flags = token; break;
            case 3: master_id = token; break;
            }
            if (i == 8) break; // Slots
        }
        if (!flags) {
            fprintf(stderr, "Invalid CLUSTER NODES reply: missing flags.\n");
            success = 0;
            goto cleanup;
        }
        int myself = (strstr(flags, "myself") != NULL);
        int is_replica = (strstr(flags, "slave") != NULL ||
                         (master_id != NULL && master_id[0] != '-'));
        if (is_replica) continue;
        if (addr == NULL) {
            fprintf(stderr, "Invalid CLUSTER NODES reply: missing addr.\n");
            success = 0;
            goto cleanup;
        }
        clusterNode *node = NULL;
        char *ip = NULL;
        int port = 0;
        char *paddr = strchr(addr, ':');
        if (paddr != NULL) {
            *paddr = '\0';
            ip = addr;
            addr = paddr + 1;
            /* If internal bus is specified, then just drop it. */
            if ((paddr = strchr(addr, '@')) != NULL) *paddr = '\0';
            port = atoi(addr);
        }
        if (myself) {
            node = firstNode;
            if (node->ip == NULL && ip != NULL) {
                node->ip = ip;
                node->port = port;
            }
        } else {
            node = createClusterNode(sdsnew(ip), port);
        }
        if (node == NULL) {
            success = 0;
            goto cleanup;
        }
        if (name != NULL) node->name = sdsnew(name);
        if (i == 8) {
            int remaining = strlen(line);
            while (remaining > 0) {
                p = strchr(line, ' ');
                if (p == NULL) p = line + remaining;
                remaining -= (p - line);

                char *slotsdef = line;
                *p = '\0';
                if (remaining) {
                    line = p + 1;
                    remaining--;
                } else line = p;
                char *dash = NULL;
                if (slotsdef[0] == '[') {
                    slotsdef++;
                    if ((p = strstr(slotsdef, "->-"))) { // Migrating
                        *p = '\0';
                        p += 3;
                        char *closing_bracket = strchr(p, ']');
                        if (closing_bracket) *closing_bracket = '\0';
                        sds slot = sdsnew(slotsdef);
                        sds dst = sdsnew(p);
                        node->migrating_count += 2;
                        node->migrating =
                            zrealloc(node->migrating,
                                (node->migrating_count * sizeof(sds)));
                        node->migrating[node->migrating_count - 2] =
                            slot;
                        node->migrating[node->migrating_count - 1] =
                            dst;
                    }  else if ((p = strstr(slotsdef, "-<-"))) {//Importing
                        *p = '\0';
                        p += 3;
                        char *closing_bracket = strchr(p, ']');
                        if (closing_bracket) *closing_bracket = '\0';
                        sds slot = sdsnew(slotsdef);
                        sds src = sdsnew(p);
                        node->importing_count += 2;
                        node->importing = zrealloc(node->importing,
                            (node->importing_count * sizeof(sds)));
                        node->importing[node->importing_count - 2] =
                            slot;
                        node->importing[node->importing_count - 1] =
                            src;
                    }
                } else if ((dash = strchr(slotsdef, '-')) != NULL) {
                    p = dash;
                    int start, stop;
                    *p = '\0';
                    start = atoi(slotsdef);
                    stop = atoi(p + 1);
                    while (start <= stop) {
                        int slot = start++;
                        node->slots[node->slots_count++] = slot;
                    }
                } else if (p > slotsdef) {
                    int slot = atoi(slotsdef);
                    node->slots[node->slots_count++] = slot;
                }
            }
        }
        if (node->slots_count == 0) {
            printf("WARNING: master node %s:%d has no slots, skipping...\n",
                   node->ip, node->port);
            continue;
        }
        if (!addClusterNode(node)) {
            success = 0;
            goto cleanup;
        }
    }
cleanup:
    if (ctx) redisFree(ctx);
    if (!success) {
        if (config.cluster_nodes) freeClusterNodes();
    }
    if (reply) freeReplyObject(reply);
    return success;
}