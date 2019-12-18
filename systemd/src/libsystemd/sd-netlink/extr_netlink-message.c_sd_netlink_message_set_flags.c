#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* uint16_t ;
struct TYPE_8__ {TYPE_1__* hdr; } ;
typedef  TYPE_2__ sd_netlink_message ;
struct TYPE_7__ {TYPE_2__* nlmsg_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_return (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sd_netlink_message_set_flags(sd_netlink_message *m, uint16_t flags) {
        assert_return(m, -EINVAL);
        assert_return(flags, -EINVAL);

        m->hdr->nlmsg_flags = flags;

        return 0;
}