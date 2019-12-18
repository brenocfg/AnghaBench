#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ type; size_t elements; int integer; char* str; struct TYPE_14__** element; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_15__ {TYPE_3__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
struct TYPE_16__ {int port; int /*<<< orphan*/  ip; } ;
typedef  TYPE_3__ clusterManagerNode ;
struct TYPE_17__ {int /*<<< orphan*/  nodes; } ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (TYPE_3__*,char*) ; 
 int CLUSTER_MANAGER_SLOTS ; 
 scalar_t__ REDIS_REPLY_ARRAY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ clusterManagerCheckRedisReply (TYPE_3__*,TYPE_1__*,char**) ; 
 TYPE_3__* clusterManagerNodeByName (char*) ; 
 TYPE_6__ cluster_manager ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static clusterManagerNode *clusterManagerGetSlotOwner(clusterManagerNode *n,
                                                      int slot, char **err)
{
    assert(slot >= 0 && slot < CLUSTER_MANAGER_SLOTS);
    clusterManagerNode *owner = NULL;
    redisReply *reply = CLUSTER_MANAGER_COMMAND(n, "CLUSTER SLOTS");
    if (clusterManagerCheckRedisReply(n, reply, err)) {
        assert(reply->type == REDIS_REPLY_ARRAY);
        size_t i;
        for (i = 0; i < reply->elements; i++) {
            redisReply *r = reply->element[i];
            assert(r->type == REDIS_REPLY_ARRAY && r->elements >= 3);
            int from, to;
            from = r->element[0]->integer;
            to = r->element[1]->integer;
            if (slot < from || slot > to) continue;
            redisReply *nr =  r->element[2];
            assert(nr->type == REDIS_REPLY_ARRAY && nr->elements >= 2);
            char *name = NULL;
            if (nr->elements >= 3)
                name =  nr->element[2]->str;
            if (name != NULL)
                owner = clusterManagerNodeByName(name);
            else {
                char *ip = nr->element[0]->str;
                assert(ip != NULL);
                int port = (int) nr->element[1]->integer;
                listIter li;
                listNode *ln;
                listRewind(cluster_manager.nodes, &li);
                while ((ln = listNext(&li)) != NULL) {
                    clusterManagerNode *nd = ln->value;
                    if (strcmp(nd->ip, ip) == 0 && port == nd->port) {
                        owner = nd;
                        break;
                    }
                }
            }
            if (owner) break;
        }
    }
    if (reply) freeReplyObject(reply);
    return owner;
}