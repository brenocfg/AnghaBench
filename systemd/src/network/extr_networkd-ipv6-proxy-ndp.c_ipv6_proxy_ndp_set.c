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
struct TYPE_6__ {int /*<<< orphan*/  ifname; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int ipv6_proxy_ndp_is_needed (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 
 int sysctl_write_ip_property_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ipv6_proxy_ndp_set(Link *link) {
        bool v;
        int r;

        assert(link);

        if (!socket_ipv6_is_supported())
                return 0;

        v = ipv6_proxy_ndp_is_needed(link);

        r = sysctl_write_ip_property_boolean(AF_INET6, link->ifname, "proxy_ndp", v);
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot configure proxy NDP for interface: %m");

        return 0;
}