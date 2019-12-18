#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct nlmsgerr {int error; } ;
struct TYPE_5__ {TYPE_4__* hdr; } ;
typedef  TYPE_1__ sd_netlink_message ;
typedef  int /*<<< orphan*/  sd_netlink ;
struct TYPE_6__ {int /*<<< orphan*/  nlmsg_seq; } ;

/* Variables and functions */
 struct nlmsgerr* NLMSG_DATA (TYPE_4__*) ; 
 int /*<<< orphan*/  NLMSG_ERROR ; 
 int /*<<< orphan*/  assert (int) ; 
 int message_new (int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ ) ; 

int rtnl_message_new_synthetic_error(sd_netlink *rtnl, int error, uint32_t serial, sd_netlink_message **ret) {
        struct nlmsgerr *err;
        int r;

        assert(error <= 0);

        r = message_new(rtnl, ret, NLMSG_ERROR);
        if (r < 0)
                return r;

        (*ret)->hdr->nlmsg_seq = serial;

        err = NLMSG_DATA((*ret)->hdr);

        err->error = error;

        return 0;
}