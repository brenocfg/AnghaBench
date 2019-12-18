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
struct ifaddrlblmsg {unsigned char ifal_prefixlen; } ;
struct TYPE_6__ {struct TYPE_6__ const* hdr; int /*<<< orphan*/  nlmsg_type; } ;
typedef  TYPE_1__ sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct ifaddrlblmsg* NLMSG_DATA (TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ const* rtnl_message_type_is_addrlabel (int /*<<< orphan*/ ) ; 

int sd_rtnl_message_addrlabel_get_prefixlen(const sd_netlink_message *m, unsigned char *prefixlen) {
        struct ifaddrlblmsg *addrlabel;

        assert_return(m, -EINVAL);
        assert_return(m->hdr, -EINVAL);
        assert_return(rtnl_message_type_is_addrlabel(m->hdr->nlmsg_type), -EINVAL);

        addrlabel = NLMSG_DATA(m->hdr);

        *prefixlen = addrlabel->ifal_prefixlen;

        return 0;
}