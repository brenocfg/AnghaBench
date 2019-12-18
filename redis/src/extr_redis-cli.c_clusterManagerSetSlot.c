#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; int len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ redisReply ;
struct TYPE_10__ {scalar_t__ name; } ;
typedef  TYPE_2__ clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (TYPE_2__*,char*,int,char const*,char*) ; 
 int /*<<< orphan*/  CLUSTER_MANAGER_PRINT_REPLY_ERROR (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* zmalloc (int) ; 

__attribute__((used)) static int clusterManagerSetSlot(clusterManagerNode *node1,
                                 clusterManagerNode *node2,
                                 int slot, const char *status, char **err) {
    redisReply *reply = CLUSTER_MANAGER_COMMAND(node1, "CLUSTER "
                                                "SETSLOT %d %s %s",
                                                slot, status,
                                                (char *) node2->name);
    if (err != NULL) *err = NULL;
    if (!reply) return 0;
    int success = 1;
    if (reply->type == REDIS_REPLY_ERROR) {
        success = 0;
        if (err != NULL) {
            *err = zmalloc((reply->len + 1) * sizeof(char));
            strcpy(*err, reply->str);
        } else CLUSTER_MANAGER_PRINT_REPLY_ERROR(node1, reply->str);
        goto cleanup;
    }
cleanup:
    freeReplyObject(reply);
    return success;
}