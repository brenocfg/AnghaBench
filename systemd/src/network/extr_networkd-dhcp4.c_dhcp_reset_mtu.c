#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct TYPE_9__ {scalar_t__ original_mtu; int /*<<< orphan*/  dhcp_lease; TYPE_1__* network; } ;
struct TYPE_8__ {int /*<<< orphan*/  dhcp_use_mtu; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_2__*) ; 
 int link_set_mtu (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  log_link_error_errno (TYPE_2__*,int,char*) ; 
 int sd_dhcp_lease_get_mtu (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int dhcp_reset_mtu(Link *link) {
        uint16_t mtu;
        int r;

        assert(link);

        if (!link->network->dhcp_use_mtu)
                return 0;

        r = sd_dhcp_lease_get_mtu(link->dhcp_lease, &mtu);
        if (r < 0)
                return r;

        if (link->original_mtu == mtu)
                return 0;

        r = link_set_mtu(link, link->original_mtu);
        if (r < 0) {
                log_link_error_errno(link, r, "DHCP error: could not reset MTU: %m");
                link_enter_failed(link);
                return r;
        }

        return 0;
}