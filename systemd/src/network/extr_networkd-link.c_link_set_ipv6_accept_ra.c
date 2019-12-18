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
struct TYPE_4__ {int flags; int /*<<< orphan*/  ifname; int /*<<< orphan*/  network; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int IFF_LOOPBACK ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  socket_ipv6_is_supported () ; 
 int sysctl_write_ip_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static int link_set_ipv6_accept_ra(Link *link) {
        int r;

        /* Make this a NOP if IPv6 is not available */
        if (!socket_ipv6_is_supported())
                return 0;

        if (link->flags & IFF_LOOPBACK)
                return 0;

        if (!link->network)
                return 0;

        r = sysctl_write_ip_property(AF_INET6, link->ifname, "accept_ra", "0");
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot disable kernel IPv6 accept_ra for interface: %m");

        return 0;
}