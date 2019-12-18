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
struct TYPE_6__ {struct TYPE_6__* event; void* time_event_source; void* io_event_source; } ;
typedef  TYPE_1__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  assert_return (TYPE_1__*,int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 TYPE_1__* sd_event_unref (TYPE_1__*) ; 

int sd_netlink_detach_event(sd_netlink *rtnl) {
        assert_return(rtnl, -EINVAL);
        assert_return(rtnl->event, -ENXIO);

        rtnl->io_event_source = sd_event_source_unref(rtnl->io_event_source);

        rtnl->time_event_source = sd_event_source_unref(rtnl->time_event_source);

        rtnl->event = sd_event_unref(rtnl->event);

        return 0;
}