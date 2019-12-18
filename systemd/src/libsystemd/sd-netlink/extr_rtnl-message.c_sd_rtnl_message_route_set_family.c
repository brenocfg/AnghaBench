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
struct rtmsg {int rtm_family; } ;
struct TYPE_6__ {struct TYPE_6__* hdr; int /*<<< orphan*/  nlmsg_type; } ;
typedef  TYPE_1__ sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rtmsg* NLMSG_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtnl_message_type_is_route (int /*<<< orphan*/ ) ; 

int sd_rtnl_message_route_set_family(sd_netlink_message *m, int family) {
        struct rtmsg *rtm;

        assert_return(m, -EINVAL);
        assert_return(m->hdr, -EINVAL);
        assert_return(rtnl_message_type_is_route(m->hdr->nlmsg_type), -EINVAL);

        rtm = NLMSG_DATA(m->hdr);

        rtm->rtm_family = family;

        return 0;
}