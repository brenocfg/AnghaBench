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
 int AF_INET ; 
 int AF_INET6 ; 
 int EINVAL ; 
 int in_addr_prefix_from_string (char const*,int,union in_addr_union*,unsigned char*) ; 
 int network_set_route (int /*<<< orphan*/ *,char const*,int,unsigned char,union in_addr_union*,union in_addr_union*) ; 
 int parse_ip_address_one (int,char const**,union in_addr_union*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strjoina (char const*,char*) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_cmdline_rd_route(Context *context, const char *key, const char *value) {
        union in_addr_union addr = {}, gateway = {};
        unsigned char prefixlen;
        const char *buf, *p;
        int family, r;

        /* rd.route=<net>/<netmask>:<gateway>[:<interface>] */

        if (proc_cmdline_value_missing(key, value))
                return -EINVAL;

        if (value[0] == '[') {
                p = strchr(value, ']');
                if (!p)
                        return -EINVAL;

                if (p[1] != ':')
                        return -EINVAL;

                buf = strndupa(value + 1, p - value - 1);
                value = p + 2;
                family = AF_INET6;
        } else {
                p = strchr(value, ':');
                if (!p)
                        return -EINVAL;

                buf = strndupa(value, p - value);
                value = p + 1;
                family = AF_INET;
        }

        r = in_addr_prefix_from_string(buf, family, &addr, &prefixlen);
        if (r < 0)
                return r;

        p = strchr(value, ':');
        if (!p)
                value = strjoina(value, ":");

        r = parse_ip_address_one(family, &value, &gateway);
        if (r < 0)
                return r;

        return network_set_route(context, value, family, prefixlen, &addr, &gateway);
}