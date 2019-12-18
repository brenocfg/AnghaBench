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
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EINVAL ; 
 int network_set_dhcp_type (int /*<<< orphan*/ *,char*,char const*) ; 
 int parse_cmdline_ip_address (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int parse_cmdline_ip_interface (int /*<<< orphan*/ *,char const*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static int parse_cmdline_ip(Context *context, const char *key, const char *value) {
        const char *p;
        int r;

        if (proc_cmdline_value_missing(key, value))
                return -EINVAL;

        p = strchr(value, ':');
        if (!p)
                /* ip={dhcp|on|any|dhcp6|auto6|either6} */
                return network_set_dhcp_type(context, "", value);

        if (value[0] == '[')
                return parse_cmdline_ip_address(context, AF_INET6, value);

        r = parse_cmdline_ip_address(context, AF_INET, value);
        if (r < 0)
                return parse_cmdline_ip_interface(context, value);

        return 0;
}