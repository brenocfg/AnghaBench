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
typedef  char* sds ;
struct TYPE_5__ {int flags; int /*<<< orphan*/ * replicas_count; int /*<<< orphan*/ * replicate; int /*<<< orphan*/  slots_count; int /*<<< orphan*/  port; int /*<<< orphan*/  ip; int /*<<< orphan*/  name; scalar_t__ dirty; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */
 int CLUSTER_MANAGER_FLAG_SLAVE ; 
 char* clusterManagerNodeFlagString (TYPE_1__*) ; 
 char* clusterManagerNodeSlotsString (TYPE_1__*) ; 
 char* sdscat (char*,char*) ; 
 char* sdscatfmt (char*,char*,char*,int /*<<< orphan*/ *,...) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 

__attribute__((used)) static sds clusterManagerNodeInfo(clusterManagerNode *node, int indent) {
    sds info = sdsempty();
    sds spaces = sdsempty();
    int i;
    for (i = 0; i < indent; i++) spaces = sdscat(spaces, " ");
    if (indent) info = sdscat(info, spaces);
    int is_master = !(node->flags & CLUSTER_MANAGER_FLAG_SLAVE);
    char *role = (is_master ? "M" : "S");
    sds slots = NULL;
    if (node->dirty && node->replicate != NULL)
        info = sdscatfmt(info, "S: %S %s:%u", node->name, node->ip, node->port);
    else {
        slots = clusterManagerNodeSlotsString(node);
        sds flags = clusterManagerNodeFlagString(node);
        info = sdscatfmt(info, "%s: %S %s:%u\n"
                               "%s   slots:%S (%u slots) "
                               "%S",
                               role, node->name, node->ip, node->port, spaces,
                               slots, node->slots_count, flags);
        sdsfree(slots);
        sdsfree(flags);
    }
    if (node->replicate != NULL)
        info = sdscatfmt(info, "\n%s   replicates %S", spaces, node->replicate);
    else if (node->replicas_count)
        info = sdscatfmt(info, "\n%s   %U additional replica(s)",
                         spaces, node->replicas_count);
    sdsfree(spaces);
    return info;
}