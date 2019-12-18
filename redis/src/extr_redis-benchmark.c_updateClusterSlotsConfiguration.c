#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int* updated_slots; int* slots; scalar_t__ updated_slots_count; scalar_t__ current_slot_index; scalar_t__ slots_count; } ;
typedef  TYPE_1__ clusterNode ;
struct TYPE_4__ {int cluster_node_count; int /*<<< orphan*/  is_updating_slots_mutex; int /*<<< orphan*/  slots_last_update; int /*<<< orphan*/  is_updating_slots; TYPE_1__** cluster_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomicIncr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomicSet (int /*<<< orphan*/ ,int) ; 
 TYPE_2__ config ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfree (int*) ; 

__attribute__((used)) static void updateClusterSlotsConfiguration() {
    pthread_mutex_lock(&config.is_updating_slots_mutex);
    atomicSet(config.is_updating_slots, 1);
    int i;
    for (i = 0; i < config.cluster_node_count; i++) {
        clusterNode *node = config.cluster_nodes[i];
        if (node->updated_slots != NULL) {
            int *oldslots = node->slots;
            node->slots = node->updated_slots;
            node->slots_count = node->updated_slots_count;
            node->current_slot_index = 0;
            node->updated_slots = NULL;
            node->updated_slots_count = 0;
            zfree(oldslots);
        }
    }
    atomicSet(config.is_updating_slots, 0);
    atomicIncr(config.slots_last_update, 1);
    pthread_mutex_unlock(&config.is_updating_slots_mutex);
}