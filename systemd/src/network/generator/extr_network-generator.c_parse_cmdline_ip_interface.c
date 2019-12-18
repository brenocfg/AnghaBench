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
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EINVAL ; 
 int network_set_dhcp_type (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_ip_mtu_mac (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_cmdline_ip_interface(Context *context, const char *value) {
        const char *ifname, *dhcp_type, *p;
        int r;

        /* ip=<interface>:{dhcp|on|any|dhcp6|auto6}[:[<mtu>][:<macaddr>]] */

        p = strchr(value, ':');
        if (!p)
                return -EINVAL;

        ifname = strndupa(value, p - value);

        value = p + 1;
        p = strchr(value, ':');
        if (!p)
                dhcp_type = value;
        else
                dhcp_type = strndupa(value, p - value);

        r = network_set_dhcp_type(context, ifname, dhcp_type);
        if (r < 0)
                return r;

        if (!p)
                return 0;

        return parse_cmdline_ip_mtu_mac(context, ifname, AF_UNSPEC, p + 1);
}