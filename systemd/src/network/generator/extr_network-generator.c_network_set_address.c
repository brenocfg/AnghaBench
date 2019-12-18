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
typedef  int /*<<< orphan*/  Network ;
typedef  int /*<<< orphan*/  Context ;

/* Variables and functions */
 int ENODEV ; 
 int address_new (int /*<<< orphan*/ *,int,unsigned char,union in_addr_union*,union in_addr_union*,int /*<<< orphan*/ *) ; 
 scalar_t__ in_addr_is_null (int,union in_addr_union*) ; 
 int /*<<< orphan*/ * network_get (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static int network_set_address(Context *context, const char *ifname, int family, unsigned char prefixlen,
                               union in_addr_union *addr, union in_addr_union *peer) {
        Network *network;

        if (in_addr_is_null(family, addr) != 0)
                return 0;

        network = network_get(context, ifname);
        if (!network)
                return -ENODEV;

        return address_new(network, family, prefixlen, addr, peer, NULL);
}