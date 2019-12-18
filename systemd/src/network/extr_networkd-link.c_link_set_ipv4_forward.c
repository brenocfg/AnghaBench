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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  link_ipv4_forward_enabled (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_link_warning_errno (int /*<<< orphan*/ *,int,char*) ; 
 int sysctl_write_ip_property (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char*) ; 

__attribute__((used)) static int link_set_ipv4_forward(Link *link) {
        int r;

        if (!link_ipv4_forward_enabled(link))
                return 0;

        /* We propagate the forwarding flag from one interface to the
         * global setting one way. This means: as long as at least one
         * interface was configured at any time that had IP forwarding
         * enabled the setting will stay on for good. We do this
         * primarily to keep IPv4 and IPv6 packet forwarding behaviour
         * somewhat in sync (see below). */

        r = sysctl_write_ip_property(AF_INET, NULL, "ip_forward", "1");
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot turn on IPv4 packet forwarding, ignoring: %m");

        return 0;
}