#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
struct ndmsg {int ndm_family; int ndm_ifindex; } ;
struct TYPE_8__ {TYPE_6__* hdr; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_9__ {int nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 TYPE_1__** IN_SET (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ndmsg* NLMSG_DATA (TYPE_6__*) ; 
 int NLM_F_APPEND ; 
 int NLM_F_CREATE ; 
 int /*<<< orphan*/  PF_BRIDGE ; 
 scalar_t__ RTM_NEWNEIGH ; 
 int /*<<< orphan*/  assert_return (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int message_new (int /*<<< orphan*/ *,TYPE_1__**,scalar_t__) ; 
 TYPE_1__** rtnl_message_type_is_neigh (scalar_t__) ; 

int sd_rtnl_message_new_neigh(sd_netlink *rtnl, sd_netlink_message **ret, uint16_t nlmsg_type, int index, int ndm_family) {
        struct ndmsg *ndm;
        int r;

        assert_return(rtnl_message_type_is_neigh(nlmsg_type), -EINVAL);
        assert_return(IN_SET(ndm_family, AF_UNSPEC, AF_INET, AF_INET6, PF_BRIDGE), -EINVAL);
        assert_return(ret, -EINVAL);

        r = message_new(rtnl, ret, nlmsg_type);
        if (r < 0)
                return r;

        if (nlmsg_type == RTM_NEWNEIGH)
                (*ret)->hdr->nlmsg_flags |= NLM_F_CREATE | NLM_F_APPEND;

        ndm = NLMSG_DATA((*ret)->hdr);

        ndm->ndm_family = ndm_family;
        ndm->ndm_ifindex = index;

        return 0;
}