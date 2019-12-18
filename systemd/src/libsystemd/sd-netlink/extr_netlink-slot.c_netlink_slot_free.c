#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  description; int /*<<< orphan*/  userdata; int /*<<< orphan*/  (* destroy_callback ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ sd_netlink_slot ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  netlink_slot_disconnect (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static sd_netlink_slot* netlink_slot_free(sd_netlink_slot *slot) {
        assert(slot);

        netlink_slot_disconnect(slot, false);

        if (slot->destroy_callback)
                slot->destroy_callback(slot->userdata);

        free(slot->description);
        return mfree(slot);
}