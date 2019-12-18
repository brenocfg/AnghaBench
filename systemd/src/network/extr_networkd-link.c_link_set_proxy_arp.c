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
struct TYPE_6__ {scalar_t__ proxy_arp; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  link_proxy_arp_enabled (TYPE_2__*) ; 
 int /*<<< orphan*/  log_link_warning_errno (TYPE_2__*,int,char*) ; 
 int sysctl_write_ip_property_boolean (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int link_set_proxy_arp(Link *link) {
        int r;

        if (!link_proxy_arp_enabled(link))
                return 0;

        r = sysctl_write_ip_property_boolean(AF_INET, link->ifname, "proxy_arp", link->network->proxy_arp > 0);
        if (r < 0)
                log_link_warning_errno(link, r, "Cannot configure proxy ARP for interface: %m");

        return 0;
}