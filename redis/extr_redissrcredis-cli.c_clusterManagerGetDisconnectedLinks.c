#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {char* str; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  list ;
typedef  int /*<<< orphan*/  clusterManagerNode ;
struct TYPE_9__ {int handshaking; scalar_t__ connected; void* node_addr; void* node_name; } ;
typedef  TYPE_2__ clusterManagerLink ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clusterManagerCheckRedisReply (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  listAddNodeTail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * listCreate () ; 
 void* sdsnew (char*) ; 
 char* strchr (char*,char) ; 
 char* strstr (char*,char*) ; 
 TYPE_2__* zmalloc (int) ; 

__attribute__((used)) static list *clusterManagerGetDisconnectedLinks(clusterManagerNode *node) {
    list *links = NULL;
    redisReply *reply = CLUSTER_MANAGER_COMMAND(node, "CLUSTER NODES");
    if (!clusterManagerCheckRedisReply(node, reply, NULL)) goto cleanup;
    links = listCreate();
    char *lines = reply->str, *p, *line;
    while ((p = strstr(lines, "\n")) != NULL) {
        int i = 0;
        *p = '\0';
        line = lines;
        lines = p + 1;
        char *nodename = NULL, *addr = NULL, *flags = NULL, *link_status = NULL;
        while ((p = strchr(line, ' ')) != NULL) {
            *p = '\0';
            char *token = line;
            line = p + 1;
            if (i == 0) nodename = token;
            else if (i == 1) addr = token;
            else if (i == 2) flags = token;
            else if (i == 7) link_status = token;
            else if (i == 8) break;
            i++;
        }
        if (i == 7) link_status = line;
        if (nodename == NULL || addr == NULL || flags == NULL ||
            link_status == NULL) continue;
        if (strstr(flags, "myself") != NULL) continue;
        int disconnected = ((strstr(flags, "disconnected") != NULL) ||
                            (strstr(link_status, "disconnected")));
        int handshaking = (strstr(flags, "handshake") != NULL);
        if (disconnected || handshaking) {
            clusterManagerLink *link = zmalloc(sizeof(*link));
            link->node_name = sdsnew(nodename);
            link->node_addr = sdsnew(addr);
            link->connected = 0;
            link->handshaking = handshaking;
            listAddNodeTail(links, link);
        }
    }
cleanup:
    if (reply != NULL) freeReplyObject(reply);
    return links;
}