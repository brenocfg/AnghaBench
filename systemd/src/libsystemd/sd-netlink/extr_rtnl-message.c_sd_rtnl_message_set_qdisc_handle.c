#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct tcmsg {int /*<<< orphan*/  tcm_handle; } ;
struct TYPE_4__ {TYPE_3__* hdr; } ;
typedef  TYPE_1__ sd_netlink_message ;
struct TYPE_5__ {int /*<<< orphan*/  nlmsg_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct tcmsg* NLMSG_DATA (TYPE_3__*) ; 
 int /*<<< orphan*/  assert_return (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_message_type_is_qdisc (int /*<<< orphan*/ ) ; 

int sd_rtnl_message_set_qdisc_handle(sd_netlink_message *m, uint32_t handle) {
        struct tcmsg *tcm;

        assert_return(rtnl_message_type_is_qdisc(m->hdr->nlmsg_type), -EINVAL);

        tcm = NLMSG_DATA(m->hdr);
        tcm->tcm_handle = handle;

        return 0;
}