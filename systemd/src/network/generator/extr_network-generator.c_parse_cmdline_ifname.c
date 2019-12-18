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
struct ether_addr {int dummy; } ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int EINVAL ; 
 int ether_addr_from_string (char const*,struct ether_addr*) ; 
 int link_new (int /*<<< orphan*/ *,char const*,struct ether_addr*,int /*<<< orphan*/ *) ; 
 scalar_t__ proc_cmdline_value_missing (char const*,char const*) ; 
 char* strchr (char const*,char) ; 
 char* strndupa (char const*,int) ; 

__attribute__((used)) static int parse_cmdline_ifname(Context *context, const char *key, const char *value) {
        struct ether_addr mac;
        const char *name, *p;
        int r;

        /* ifname=<interface>:<MAC> */

        if (proc_cmdline_value_missing(key, value))
                return -EINVAL;

        p = strchr(value, ':');
        if (!p)
                return -EINVAL;

        name = strndupa(value, p - value);

        r = ether_addr_from_string(p + 1, &mac);
        if (r < 0)
                return r;

        return link_new(context, name, &mac, NULL);
}