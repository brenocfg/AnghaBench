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
typedef  union sockaddr_union {int dummy; } sockaddr_union ;
struct sockaddr_in {int dummy; } ;
typedef  int /*<<< orphan*/  sd_netlink_message ;

/* Variables and functions */
 int netlink_message_append_sockaddr_union (int /*<<< orphan*/ *,unsigned short,union sockaddr_union const*) ; 

int sd_netlink_message_append_sockaddr_in(sd_netlink_message *m, unsigned short type, const struct sockaddr_in *data) {
        return netlink_message_append_sockaddr_union(m, type, (const union sockaddr_union *) data);
}