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
struct nlmsgerr {int error; } ;
struct TYPE_6__ {struct TYPE_6__ const* hdr; } ;
typedef  TYPE_1__ sd_netlink_message ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct nlmsgerr* NLMSG_DATA (TYPE_1__ const*) ; 
 int /*<<< orphan*/  assert_return (TYPE_1__ const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_netlink_message_is_error (TYPE_1__ const*) ; 

int sd_netlink_message_get_errno(const sd_netlink_message *m) {
        struct nlmsgerr *err;

        assert_return(m, -EINVAL);
        assert_return(m->hdr, -EINVAL);

        if (!sd_netlink_message_is_error(m))
                return 0;

        err = NLMSG_DATA(m->hdr);

        return err->error;
}