#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* hdr; } ;
typedef  TYPE_2__ sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_F_REPLACE ; 
 int /*<<< orphan*/  RTM_NEWADDR ; 
 int sd_rtnl_message_new_addr (int /*<<< orphan*/ *,TYPE_2__**,int /*<<< orphan*/ ,int,int) ; 

int sd_rtnl_message_new_addr_update(sd_netlink *rtnl, sd_netlink_message **ret,
                             int index, int family) {
        int r;

        r = sd_rtnl_message_new_addr(rtnl, ret, RTM_NEWADDR, index, family);
        if (r < 0)
                return r;

        (*ret)->hdr->nlmsg_flags |= NLM_F_REPLACE;

        return 0;
}