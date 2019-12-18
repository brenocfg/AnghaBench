#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int floating; int /*<<< orphan*/  netlink; } ;
typedef  TYPE_1__ sd_netlink_slot ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int ESTALE ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_slot_ref (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_netlink_slot_unref (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_netlink_unref (int /*<<< orphan*/ ) ; 

int sd_netlink_slot_set_floating(sd_netlink_slot *slot, int b) {
        assert_return(slot, -EINVAL);

        if (slot->floating == !!b)
                return 0;

        if (!slot->netlink) /* Already disconnected */
                return -ESTALE;

        slot->floating = b;

        if (b) {
                sd_netlink_slot_ref(slot);
                sd_netlink_unref(slot->netlink);
        } else {
                sd_netlink_ref(slot->netlink);
                sd_netlink_slot_unref(slot);
        }

        return 1;
}