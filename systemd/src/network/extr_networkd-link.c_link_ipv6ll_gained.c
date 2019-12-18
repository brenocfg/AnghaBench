#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct in6_addr {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  state; struct in6_addr ipv6ll_address; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINK_STATE_CONFIGURED ; 
 int /*<<< orphan*/  LINK_STATE_CONFIGURING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int link_acquire_ipv6_conf (TYPE_1__*) ; 
 int /*<<< orphan*/  link_check_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  link_enter_failed (TYPE_1__*) ; 
 int /*<<< orphan*/  log_link_info (TYPE_1__*,char*) ; 

int link_ipv6ll_gained(Link *link, const struct in6_addr *address) {
        int r;

        assert(link);

        log_link_info(link, "Gained IPv6LL");

        link->ipv6ll_address = *address;
        link_check_ready(link);

        if (IN_SET(link->state, LINK_STATE_CONFIGURING, LINK_STATE_CONFIGURED)) {
                r = link_acquire_ipv6_conf(link);
                if (r < 0) {
                        link_enter_failed(link);
                        return r;
                }
        }

        return 0;
}