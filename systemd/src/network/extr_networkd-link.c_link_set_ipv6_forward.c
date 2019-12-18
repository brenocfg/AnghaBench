#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  link_ipv6_forward_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_link_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sysctl_write_ip_property (int /*<<< orphan*/ ,char*,char*,char*) ; 

__attribute__((used)) static int link_set_ipv6_forward(Link *link) {
        int r;

        if (!link_ipv6_forward_enabled(link))
                return 0;

        /* On Linux, the IPv6 stack does not know a per-interface
         * packet forwarding setting: either packet forwarding is on
         * for all, or off for all. We hence don't bother with a
         * per-interface setting, but simply propagate the interface
         * flag, if it is set, to the global flag, one-way. Note that
         * while IPv4 would allow a per-interface flag, we expose the
         * same behaviour there and also propagate the setting from
         * one to all, to keep things simple (see above). */

        r = sysctl_write_ip_property(AF_INET6, "all", "forwarding", "1");
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot configure IPv6 packet forwarding, ignoring: %m");

        return 0;
}