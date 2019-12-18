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
struct in_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int netlink_message_append_in_addr_union (int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ,union in_addr_union const*) ; 

int sd_netlink_message_append_in_addr(sd_netlink_message *m, unsigned short type, const struct in_addr *data) {
        return netlink_message_append_in_addr_union(m, type, AF_INET, (const union in_addr_union *) data);
}