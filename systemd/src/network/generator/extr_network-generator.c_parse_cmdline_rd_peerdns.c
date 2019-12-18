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
 int network_set_dhcp_use_dns (int /*<<< orphan*/ *,char*,int) ; 
 int parse_boolean (char const*) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 

__attribute__((used)) static int parse_cmdline_rd_peerdns(Context *context, const char *key, const char *value) {
        int r;

        if (proc_cmdline_value_missing(key, value))
                return network_set_dhcp_use_dns(context, "", true);

        r = parse_boolean(value);
        if (r < 0)
                return r;

        return network_set_dhcp_use_dns(context, "", r);
}