#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int tracking_table_max_fill; } ;

/* Variables and functions */
 int TRACKING_TABLE_SIZE ; 
 int /*<<< orphan*/ ** TrackingTable ; 
 unsigned int TrackingTableUsedSlots ; 
 int rand () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  trackingInvalidateSlot (unsigned int) ; 

void trackingLimitUsedSlots(void) {
    static unsigned int timeout_counter = 0;

    if (server.tracking_table_max_fill == 0) return; /* No limits set. */
    unsigned int max_slots =
        (TRACKING_TABLE_SIZE/100) * server.tracking_table_max_fill;
    if (TrackingTableUsedSlots <= max_slots) {
        timeout_counter = 0;
        return; /* Limit not reached. */
    }

    /* We have to invalidate a few slots to reach the limit again. The effort
     * we do here is proportional to the number of times we entered this
     * function and found that we are still over the limit. */
    int effort = 100 * (timeout_counter+1);

    /* Let's start at a random position, and perform linear probing, in order
     * to improve cache locality. However once we are able to find an used
     * slot, jump again randomly, in order to avoid creating big holes in the
     * table (that will make this funciton use more resourced later). */
    while(effort > 0) {
        unsigned int idx = rand() % TRACKING_TABLE_SIZE;
        do {
            effort--;
            idx = (idx+1) % TRACKING_TABLE_SIZE;
            if (TrackingTable[idx] != NULL) {
                trackingInvalidateSlot(idx);
                if (TrackingTableUsedSlots <= max_slots) {
                    timeout_counter = 0;
                    return; /* Return ASAP: we are again under the limit. */
                } else {
                    break; /* Jump to next random position. */
                }
            }
        } while(effort > 0);
    }
    timeout_counter++;
}