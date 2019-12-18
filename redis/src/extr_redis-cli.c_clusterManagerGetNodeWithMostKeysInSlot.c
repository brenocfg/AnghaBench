#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int integer; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_13__ {TYPE_3__* value; } ;
typedef  TYPE_2__ listNode ;
typedef  int /*<<< orphan*/  listIter ;
typedef  int /*<<< orphan*/  list ;
struct TYPE_14__ {int flags; scalar_t__ replicate; } ;
typedef  TYPE_3__ clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (TYPE_3__*,char*,int) ; 
 int CLUSTER_MANAGER_FLAG_SLAVE ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (TYPE_3__*,char**) ; 
 int clusterManagerCheckRedisReply (TYPE_3__*,TYPE_1__*,char**) ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 TYPE_2__* listNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  listRewind (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static clusterManagerNode * clusterManagerGetNodeWithMostKeysInSlot(list *nodes,
                                                                    int slot,
                                                                    char **err)
{
    clusterManagerNode *node = NULL;
    int numkeys = 0;
    listIter li;
    listNode *ln;
    listRewind(nodes, &li);
    if (err) *err = NULL;
    while ((ln = listNext(&li)) != NULL) {
        clusterManagerNode *n = ln->value;
        if (n->flags & CLUSTER_MANAGER_FLAG_SLAVE || n->replicate)
            continue;
        redisReply *r =
            CLUSTER_MANAGER_COMMAND(n, "CLUSTER COUNTKEYSINSLOT %d", slot);
        int success = clusterManagerCheckRedisReply(n, r, err);
        if (success) {
            if (r->integer > numkeys || node == NULL) {
                numkeys = r->integer;
                node = n;
            }
        }
        if (r != NULL) freeReplyObject(r);
        /* If the reply contains errors */
        if (!success) {
            if (err != NULL && *err != NULL)
                CLUSTER_MANAGER_PRINT_REPLY_ERROR(n, err);
            node = NULL;
            break;
        }
    }
    return node;
}