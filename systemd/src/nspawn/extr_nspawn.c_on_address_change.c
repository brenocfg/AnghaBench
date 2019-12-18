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
typedef  union in_addr_union sd_netlink_message ;
typedef  union in_addr_union sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  arg_expose_ports ; 
 int /*<<< orphan*/  assert (union in_addr_union*) ; 
 int /*<<< orphan*/  expose_port_execute (union in_addr_union*,int /*<<< orphan*/ ,union in_addr_union*) ; 

__attribute__((used)) static int on_address_change(sd_netlink *rtnl, sd_netlink_message *m, void *userdata) {
        union in_addr_union *exposed = userdata;

        assert(rtnl);
        assert(m);
        assert(exposed);

        expose_port_execute(rtnl, arg_expose_ports, exposed);
        return 0;
}