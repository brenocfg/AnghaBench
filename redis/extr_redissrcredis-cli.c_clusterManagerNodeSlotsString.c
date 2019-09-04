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
typedef  int /*<<< orphan*/  sds ;
struct TYPE_3__ {int* slots; } ;
typedef  TYPE_1__ clusterManagerNode ;

/* Variables and functions */
 int CLUSTER_MANAGER_SLOTS ; 
 int /*<<< orphan*/  sdscat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sdscatfmt (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sdsempty () ; 
 scalar_t__ sdslen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sds clusterManagerNodeSlotsString(clusterManagerNode *node) {
    sds slots = sdsempty();
    int first_range_idx = -1, last_slot_idx = -1, i;
    for (i = 0; i < CLUSTER_MANAGER_SLOTS; i++) {
        int has_slot = node->slots[i];
        if (has_slot) {
            if (first_range_idx == -1) {
                if (sdslen(slots)) slots = sdscat(slots, ",");
                first_range_idx = i;
                slots = sdscatfmt(slots, "[%u", i);
            }
            last_slot_idx = i;
        } else {
            if (last_slot_idx >= 0) {
                if (first_range_idx == last_slot_idx)
                    slots = sdscat(slots, "]");
                else slots = sdscatfmt(slots, "-%u]", last_slot_idx);
            }
            last_slot_idx = -1;
            first_range_idx = -1;
        }
    }
    if (last_slot_idx >= 0) {
        if (first_range_idx == last_slot_idx) slots = sdscat(slots, "]");
        else slots = sdscatfmt(slots, "-%u]", last_slot_idx);
    }
    return slots;
}