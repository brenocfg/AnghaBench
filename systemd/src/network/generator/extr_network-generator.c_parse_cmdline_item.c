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
 int /*<<< orphan*/  assert (void*) ; 
 int parse_cmdline_bond (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_bridge (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_ifname (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_ip (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_nameserver (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_rd_peerdns (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_rd_route (int /*<<< orphan*/ *,char const*,char const*) ; 
 int parse_cmdline_vlan (int /*<<< orphan*/ *,char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int parse_cmdline_item(const char *key, const char *value, void *data) {
        Context *context = data;

        assert(key);
        assert(data);

        if (streq(key, "ip"))
                return parse_cmdline_ip(context, key, value);
        if (streq(key, "rd.route"))
                return parse_cmdline_rd_route(context, key, value);
        if (streq(key, "nameserver"))
                return parse_cmdline_nameserver(context, key, value);
        if (streq(key, "rd.peerdns"))
                return parse_cmdline_rd_peerdns(context, key, value);
        if (streq(key, "vlan"))
                return parse_cmdline_vlan(context, key, value);
        if (streq(key, "bridge"))
                return parse_cmdline_bridge(context, key, value);
        if (streq(key, "bond"))
                return parse_cmdline_bond(context, key, value);
        if (streq(key, "ifname"))
                return parse_cmdline_ifname(context, key, value);

        return 0;
}