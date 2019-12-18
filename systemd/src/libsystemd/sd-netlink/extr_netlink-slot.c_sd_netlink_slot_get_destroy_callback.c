#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  destroy_callback; } ;
typedef  TYPE_1__ sd_netlink_slot ;
typedef  int /*<<< orphan*/  sd_netlink_destroy_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_1__ const*,int /*<<< orphan*/ ) ; 

int sd_netlink_slot_get_destroy_callback(const sd_netlink_slot *slot, sd_netlink_destroy_t *callback) {
        assert_return(slot, -EINVAL);

        if (callback)
                *callback = slot->destroy_callback;

        return !!slot->destroy_callback;
}