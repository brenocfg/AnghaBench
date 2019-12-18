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
typedef  scalar_t__ usec_t ;
typedef  scalar_t__ uint64_t ;
struct timespec {int dummy; } ;
struct pollfd {int events; int /*<<< orphan*/  fd; } ;
struct TYPE_6__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ sd_netlink ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int POLLIN ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int ppoll (struct pollfd*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sd_netlink_get_events (TYPE_1__*) ; 
 int sd_netlink_get_timeout (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/ * timespec_store (struct timespec*,scalar_t__) ; 

__attribute__((used)) static int rtnl_poll(sd_netlink *rtnl, bool need_more, uint64_t timeout_usec) {
        struct pollfd p[1] = {};
        struct timespec ts;
        usec_t m = USEC_INFINITY;
        int r, e;

        assert(rtnl);

        e = sd_netlink_get_events(rtnl);
        if (e < 0)
                return e;

        if (need_more)
                /* Caller wants more data, and doesn't care about
                 * what's been read or any other timeouts. */
                e |= POLLIN;
        else {
                usec_t until;
                /* Caller wants to process if there is something to
                 * process, but doesn't care otherwise */

                r = sd_netlink_get_timeout(rtnl, &until);
                if (r < 0)
                        return r;
                if (r > 0) {
                        usec_t nw;
                        nw = now(CLOCK_MONOTONIC);
                        m = until > nw ? until - nw : 0;
                }
        }

        if (timeout_usec != (uint64_t) -1 && (m == (uint64_t) -1 || timeout_usec < m))
                m = timeout_usec;

        p[0].fd = rtnl->fd;
        p[0].events = e;

        r = ppoll(p, 1, m == (uint64_t) -1 ? NULL : timespec_store(&ts, m), NULL);
        if (r < 0)
                return -errno;

        return r > 0 ? 1 : 0;
}