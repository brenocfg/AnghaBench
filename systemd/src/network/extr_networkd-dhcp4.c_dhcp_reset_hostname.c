#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  manager; int /*<<< orphan*/  dhcp_lease; TYPE_1__* network; } ;
struct TYPE_6__ {char* dhcp_hostname; int /*<<< orphan*/  dhcp_use_hostname; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int log_link_error_errno (TYPE_2__*,int,char*) ; 
 int manager_set_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_dhcp_lease_get_hostname (int /*<<< orphan*/ ,char const**) ; 

__attribute__((used)) static int dhcp_reset_hostname(Link *link) {
        const char *hostname;
        int r;

        assert(link);

        if (!link->network->dhcp_use_hostname)
                return 0;

        hostname = link->network->dhcp_hostname;
        if (!hostname)
                (void) sd_dhcp_lease_get_hostname(link->dhcp_lease, &hostname);

        if (!hostname)
                return 0;

        /* If a hostname was set due to the lease, then unset it now. */
        r = manager_set_hostname(link->manager, NULL);
        if (r < 0)
                return log_link_error_errno(link, r, "DHCP error: Failed to reset transient hostname: %m");

        return 0;
}