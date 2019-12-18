#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct rtmsg {int rtm_family; int /*<<< orphan*/  rtm_type; int /*<<< orphan*/  rtm_scope; int /*<<< orphan*/  rtm_protocol; } ;
struct TYPE_7__ {TYPE_6__* hdr; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_8__ {int nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct rtmsg* NLMSG_DATA (TYPE_6__*) ; 
 int NLM_F_CREATE ; 
 int NLM_F_EXCL ; 
 scalar_t__ RTM_NEWRULE ; 
 int /*<<< orphan*/  RTN_UNICAST ; 
 int /*<<< orphan*/  RTPROT_BOOT ; 
 int /*<<< orphan*/  RT_SCOPE_UNIVERSE ; 
 int /*<<< orphan*/  assert_return (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int message_new (int /*<<< orphan*/ *,TYPE_1__**,scalar_t__) ; 
 TYPE_1__** rtnl_message_type_is_routing_policy_rule (scalar_t__) ; 

int sd_rtnl_message_new_routing_policy_rule(sd_netlink *rtnl, sd_netlink_message **ret, uint16_t nlmsg_type, int ifal_family) {
        struct rtmsg *rtm;
        int r;

        assert_return(rtnl_message_type_is_routing_policy_rule(nlmsg_type), -EINVAL);
        assert_return(ret, -EINVAL);

        r = message_new(rtnl, ret, nlmsg_type);
        if (r < 0)
                return r;

        if (nlmsg_type == RTM_NEWRULE)
                (*ret)->hdr->nlmsg_flags |= NLM_F_CREATE | NLM_F_EXCL;

        rtm = NLMSG_DATA((*ret)->hdr);
        rtm->rtm_family = ifal_family;
        rtm->rtm_protocol = RTPROT_BOOT;
        rtm->rtm_scope = RT_SCOPE_UNIVERSE;
        rtm->rtm_type = RTN_UNICAST;

        return 0;
}