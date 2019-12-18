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
typedef  union in_addr_union {int dummy; } in_addr_union ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int /*<<< orphan*/  AF_UNSPEC ; 
 int EINVAL ; 
 int /*<<< orphan*/  hostname_is_valid (char const*,int) ; 
 int network_set_address (int /*<<< orphan*/ *,char const*,int,unsigned char,union in_addr_union*,union in_addr_union*) ; 
 int network_set_dhcp_type (int /*<<< orphan*/ *,char const*,char const*) ; 
 int network_set_dns (int /*<<< orphan*/ *,char const*,char const*) ; 
 int network_set_hostname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int network_set_route (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,union in_addr_union*) ; 
 int parse_cmdline_ip_mtu_mac (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*) ; 
 int parse_ip_address_one (int,char const**,union in_addr_union*) ; 
 int parse_netmask_or_prefixlen (int,char const**,unsigned char*) ; 
 char* strchr (char const*,char) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_cmdline_ip_address(Context *context, int family, const char *value) {
        union in_addr_union addr = {}, peer = {}, gateway = {};
        const char *hostname, *ifname, *dhcp_type, *dns, *p;
        unsigned char prefixlen;
        int r;

        /* ip=<client-IP>:[<peer>]:<gateway-IP>:<netmask>:<client_hostname>:<interface>:{none|off|dhcp|on|any|dhcp6|auto6|ibft}[:[<mtu>][:<macaddr>]]
         * ip=<client-IP>:[<peer>]:<gateway-IP>:<netmask>:<client_hostname>:<interface>:{none|off|dhcp|on|any|dhcp6|auto6|ibft}[:[<dns1>][:<dns2>]] */

        r = parse_ip_address_one(family, &value, &addr);
        if (r < 0)
                return r;
        r = parse_ip_address_one(family, &value, &peer);
        if (r < 0)
                return r;
        r = parse_ip_address_one(family, &value, &gateway);
        if (r < 0)
                return r;
        r = parse_netmask_or_prefixlen(family, &value, &prefixlen);
        if (r < 0)
                return r;

        /* hostname */
        p = strchr(value, ':');
        if (!p)
                return -EINVAL;

        hostname = strndupa(value, p - value);
        if (!hostname_is_valid(hostname, false))
                return -EINVAL;

        value = p + 1;

        /* ifname */
        p = strchr(value, ':');
        if (!p)
                return -EINVAL;

        ifname = strndupa(value, p - value);

        value = p + 1;

        /* dhcp_type */
        p = strchr(value, ':');
        if (!p)
                dhcp_type = value;
        else
                dhcp_type = strndupa(value, p - value);

        r = network_set_dhcp_type(context, ifname, dhcp_type);
        if (r < 0)
                return r;

        /* set values */
        r = network_set_hostname(context, ifname, hostname);
        if (r < 0)
                return r;

        r = network_set_address(context, ifname, family, prefixlen, &addr, &peer);
        if (r < 0)
                return r;

        r = network_set_route(context, ifname, family, 0, NULL, &gateway);
        if (r < 0)
                return r;

        if (!p)
                return 0;

        /* First, try [<mtu>][:<macaddr>] */
        r = parse_cmdline_ip_mtu_mac(context, ifname, AF_UNSPEC, p + 1);
        if (r >= 0)
                return 0;

        /* Next, try [<dns1>][:<dns2>] */
        value = p + 1;
        p = strchr(value, ':');
        if (!p) {
                r = network_set_dns(context, ifname, value);
                if (r < 0)
                        return r;
        } else {
                dns = strndupa(value, p - value);
                r = network_set_dns(context, ifname, dns);
                if (r < 0)
                        return r;
                r = network_set_dns(context, ifname, p + 1);
                if (r < 0)
                        return r;
        }

        return 0;
}