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
typedef  int /*<<< orphan*/  NLTypeSystem ;

/* Variables and functions */
#define  NETLINK_GENERIC 128 
 int /*<<< orphan*/  const genl_type_system_root ; 
 int /*<<< orphan*/  const rtnl_type_system_root ; 

const NLTypeSystem *type_system_get_root(int protocol) {
        switch (protocol) {
                case NETLINK_GENERIC:
                        return &genl_type_system_root;
                default: /* NETLINK_ROUTE: */
                        return &rtnl_type_system_root;
        }
}