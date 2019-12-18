#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct nhmsg {int /*<<< orphan*/  nh_flags; } ;
struct TYPE_6__ {struct TYPE_6__* hdr; int /*<<< orphan*/  nlmsg_type; } ;
typedef  TYPE_1__ sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nhmsg* NLMSG_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtnl_message_type_is_nexthop (int /*<<< orphan*/ ) ; 

int sd_rtnl_message_nexthop_set_flags(sd_netlink_message *m, uint8_t flags) {
        struct nhmsg *nhm;

        assert_return(m, -EINVAL);
        assert_return(m->hdr, -EINVAL);
        assert_return(rtnl_message_type_is_nexthop(m->hdr->nlmsg_type), -EINVAL);

        nhm = NLMSG_DATA(m->hdr);
        nhm->nh_flags |= flags;

        return 0;
}