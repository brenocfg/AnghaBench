#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_netlink ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int sd_netlink_process (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int time_callback(sd_event_source *s, uint64_t usec, void *userdata) {
        sd_netlink *rtnl = userdata;
        int r;

        assert(rtnl);

        r = sd_netlink_process(rtnl, NULL);
        if (r < 0)
                return r;

        return 1;
}