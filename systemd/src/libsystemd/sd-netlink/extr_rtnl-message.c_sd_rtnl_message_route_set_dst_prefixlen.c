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
struct rtmsg {scalar_t__ rtm_family; unsigned char rtm_dst_len; } ;
struct TYPE_6__ {struct TYPE_6__* hdr; int /*<<< orphan*/  nlmsg_type; } ;
typedef  TYPE_1__ sd_netlink_message ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  EINVAL ; 
 int ERANGE ; 
 struct rtmsg* NLMSG_DATA (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* rtnl_message_type_is_route (int /*<<< orphan*/ ) ; 

int sd_rtnl_message_route_set_dst_prefixlen(sd_netlink_message *m, unsigned char prefixlen) {
        struct rtmsg *rtm;

        assert_return(m, -EINVAL);
        assert_return(m->hdr, -EINVAL);
        assert_return(rtnl_message_type_is_route(m->hdr->nlmsg_type), -EINVAL);

        rtm = NLMSG_DATA(m->hdr);

        if ((rtm->rtm_family == AF_INET && prefixlen > 32) ||
            (rtm->rtm_family == AF_INET6 && prefixlen > 128))
                return -ERANGE;

        rtm->rtm_dst_len = prefixlen;

        return 0;
}