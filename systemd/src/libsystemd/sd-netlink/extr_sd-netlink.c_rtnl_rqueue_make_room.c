#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ rqueue_size; int /*<<< orphan*/  rqueue_allocated; int /*<<< orphan*/  rqueue; } ;
typedef  TYPE_1__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  ENOBUFS ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ RTNL_RQUEUE_MAX ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_debug_errno (int /*<<< orphan*/ ,char*,scalar_t__) ; 

int rtnl_rqueue_make_room(sd_netlink *rtnl) {
        assert(rtnl);

        if (rtnl->rqueue_size >= RTNL_RQUEUE_MAX)
                return log_debug_errno(SYNTHETIC_ERRNO(ENOBUFS),
                                       "rtnl: exhausted the read queue size (%d)",
                                       RTNL_RQUEUE_MAX);

        if (!GREEDY_REALLOC(rtnl->rqueue, rtnl->rqueue_allocated, rtnl->rqueue_size + 1))
                return -ENOMEM;

        return 0;
}