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
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_4__ {int /*<<< orphan*/  dns; } ;
typedef  TYPE_1__ Network ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int in_addr_from_string_auto (char const*,int*,union in_addr_union*) ; 
 TYPE_1__* network_get (int /*<<< orphan*/ *,char const*) ; 
 int network_new (int /*<<< orphan*/ *,char const*,TYPE_1__**) ; 
 int strv_extend (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int network_set_dns(Context *context, const char *ifname, const char *dns) {
        union in_addr_union a;
        Network *network;
        int family, r;

        r = in_addr_from_string_auto(dns, &family, &a);
        if (r < 0)
                return r;

        network = network_get(context, ifname);
        if (!network) {
                r = network_new(context, ifname, &network);
                if (r < 0)
                        return r;
        }

        return strv_extend(&network->dns, dns);
}