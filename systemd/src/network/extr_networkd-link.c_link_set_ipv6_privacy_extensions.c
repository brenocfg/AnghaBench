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
struct TYPE_7__ {TYPE_1__* network; int /*<<< orphan*/  ifname; } ;
struct TYPE_6__ {scalar_t__ ipv6_privacy_extensions; } ;
typedef  TYPE_2__ Link ;
typedef  scalar_t__ IPv6PrivacyExtensions ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 scalar_t__ link_ipv6_privacy_extensions (TYPE_2__*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_2__*,int,char*) ; 
 int sysctl_write_ip_property_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int link_set_ipv6_privacy_extensions(Link *link) {
        IPv6PrivacyExtensions s;
        int r;

        s = link_ipv6_privacy_extensions(link);
        if (s < 0)
                return 0;

        r = sysctl_write_ip_property_int(AF_INET6, link->ifname, "use_tempaddr", (int) link->network->ipv6_privacy_extensions);
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot configure IPv6 privacy extension for interface: %m");

        return 0;
}