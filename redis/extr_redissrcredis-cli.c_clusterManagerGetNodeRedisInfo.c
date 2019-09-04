#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; int len; int /*<<< orphan*/  str; } ;
typedef  TYPE_1__ redisReply ;
typedef  int /*<<< orphan*/  clusterManagerNode ;

/* Variables and functions */
 TYPE_1__* CLUSTER_MANAGER_COMMAND (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ REDIS_REPLY_ERROR ; 
 int /*<<< orphan*/  freeReplyObject (TYPE_1__*) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 char* zmalloc (int) ; 

__attribute__((used)) static redisReply *clusterManagerGetNodeRedisInfo(clusterManagerNode *node,
                                                  char **err)
{
    redisReply *info = CLUSTER_MANAGER_COMMAND(node, "INFO");
    if (err != NULL) *err = NULL;
    if (info == NULL) return NULL;
    if (info->type == REDIS_REPLY_ERROR) {
        if (err != NULL) {
            *err = zmalloc((info->len + 1) * sizeof(char));
            strcpy(*err, info->str);
        }
        freeReplyObject(info);
        return  NULL;
    }
    return info;
}