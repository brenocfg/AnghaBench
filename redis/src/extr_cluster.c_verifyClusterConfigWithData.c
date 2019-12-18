#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int cluster_module_flags; int dbnum; TYPE_2__* cluster; TYPE_1__* db; } ;
struct TYPE_5__ {int /*<<< orphan*/ ** slots; int /*<<< orphan*/ ** importing_slots_from; } ;
struct TYPE_4__ {int /*<<< orphan*/  dict; } ;

/* Variables and functions */
 int CLUSTER_MODULE_FLAG_NO_REDIRECTION ; 
 int CLUSTER_SLOTS ; 
 int C_ERR ; 
 int C_OK ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  clusterAddSlot (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  clusterSaveConfigOrDie (int) ; 
 int /*<<< orphan*/  countKeysInSlot (int) ; 
 scalar_t__ dictSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * myself ; 
 scalar_t__ nodeIsSlave (int /*<<< orphan*/ *) ; 
 TYPE_3__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,int) ; 

int verifyClusterConfigWithData(void) {
    int j;
    int update_config = 0;

    /* Return ASAP if a module disabled cluster redirections. In that case
     * every master can store keys about every possible hash slot. */
    if (server.cluster_module_flags & CLUSTER_MODULE_FLAG_NO_REDIRECTION)
        return C_OK;

    /* If this node is a slave, don't perform the check at all as we
     * completely depend on the replication stream. */
    if (nodeIsSlave(myself)) return C_OK;

    /* Make sure we only have keys in DB0. */
    for (j = 1; j < server.dbnum; j++) {
        if (dictSize(server.db[j].dict)) return C_ERR;
    }

    /* Check that all the slots we see populated memory have a corresponding
     * entry in the cluster table. Otherwise fix the table. */
    for (j = 0; j < CLUSTER_SLOTS; j++) {
        if (!countKeysInSlot(j)) continue; /* No keys in this slot. */
        /* Check if we are assigned to this slot or if we are importing it.
         * In both cases check the next slot as the configuration makes
         * sense. */
        if (server.cluster->slots[j] == myself ||
            server.cluster->importing_slots_from[j] != NULL) continue;

        /* If we are here data and cluster config don't agree, and we have
         * slot 'j' populated even if we are not importing it, nor we are
         * assigned to this slot. Fix this condition. */

        update_config++;
        /* Case A: slot is unassigned. Take responsibility for it. */
        if (server.cluster->slots[j] == NULL) {
            serverLog(LL_WARNING, "I have keys for unassigned slot %d. "
                                    "Taking responsibility for it.",j);
            clusterAddSlot(myself,j);
        } else {
            serverLog(LL_WARNING, "I have keys for slot %d, but the slot is "
                                    "assigned to another node. "
                                    "Setting it to importing state.",j);
            server.cluster->importing_slots_from[j] = server.cluster->slots[j];
        }
    }
    if (update_config) clusterSaveConfigOrDie(1);
    return C_OK;
}