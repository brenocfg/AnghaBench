#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* ip; int port; int /*<<< orphan*/ * redis_config; scalar_t__ importing_count; scalar_t__ migrating_count; int /*<<< orphan*/ * importing; int /*<<< orphan*/ * migrating; scalar_t__ updated_slots_count; int /*<<< orphan*/ * updated_slots; scalar_t__ current_slot_index; scalar_t__ slots_count; void* slots; scalar_t__ replicas_count; int /*<<< orphan*/ * replicate; scalar_t__ flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ clusterNode ;

/* Variables and functions */
 int CLUSTER_SLOTS ; 
 void* zmalloc (int) ; 

__attribute__((used)) static clusterNode *createClusterNode(char *ip, int port) {
    clusterNode *node = zmalloc(sizeof(*node));
    if (!node) return NULL;
    node->ip = ip;
    node->port = port;
    node->name = NULL;
    node->flags = 0;
    node->replicate = NULL;
    node->replicas_count = 0;
    node->slots = zmalloc(CLUSTER_SLOTS * sizeof(int));
    node->slots_count = 0;
    node->current_slot_index = 0;
    node->updated_slots = NULL;
    node->updated_slots_count = 0;
    node->migrating = NULL;
    node->importing = NULL;
    node->migrating_count = 0;
    node->importing_count = 0;
    node->redis_config = NULL;
    return node;
}