#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_CONFIGURED ; 
 int /*<<< orphan*/  LINK_STATE_CONFIGURING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int link_acquire_conf (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int link_handle_bound_by_list (TYPE_1__*) ; 
 int link_reconfigure (TYPE_1__*,int) ; 
 int link_request_set_addresses (TYPE_1__*) ; 
 int /*<<< orphan*/  link_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int wifi_get_info (TYPE_1__*) ; 

__attribute__((used)) static int link_carrier_gained(Link *link) {
        int r;

        assert(link);

        r = wifi_get_info(link);
        if (r < 0)
                return r;
        if (r > 0) {
                r = link_reconfigure(link, false);
                if (r < 0)
                        return r;
        }

        if (IN_SET(link->state, LINK_STATE_CONFIGURING, LINK_STATE_CONFIGURED)) {
                r = link_acquire_conf(link);
                if (r < 0) {
                        link_enter_failed(link);
                        return r;
                }

                link_set_state(link, LINK_STATE_CONFIGURING);
                r = link_request_set_addresses(link);
                if (r < 0)
                        return r;
        }

        r = link_handle_bound_by_list(link);
        if (r < 0)
                return r;

        return 0;
}