#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_14__ {struct TYPE_14__* manager; struct TYPE_14__* network; } ;
typedef  TYPE_1__ sd_ndisc_router ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int EBUSY ; 
 int ND_RA_FLAG_MANAGED ; 
 int ND_RA_FLAG_OTHER ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dhcp6_request_address (TYPE_1__*,int) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 
 int /*<<< orphan*/  ndisc_router_process_default (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ndisc_router_process_options (TYPE_1__*,TYPE_1__*) ; 
 int sd_ndisc_router_get_flags (TYPE_1__*,int*) ; 

__attribute__((used)) static int ndisc_router_handler(Link *link, sd_ndisc_router *rt) {
        uint64_t flags;
        int r;

        assert(link);
        assert(link->network);
        assert(link->manager);
        assert(rt);

        r = sd_ndisc_router_get_flags(rt, &flags);
        if (r < 0)
                return log_link_warning_errno(link, r, "Failed to get RA flags: %m");

        if (flags & (ND_RA_FLAG_MANAGED | ND_RA_FLAG_OTHER)) {
                /* (re)start DHCPv6 client in stateful or stateless mode according to RA flags */
                r = dhcp6_request_address(link, !(flags & ND_RA_FLAG_MANAGED));
                if (r < 0 && r != -EBUSY)
                        log_link_warning_errno(link, r, "Could not acquire DHCPv6 lease on NDisc request: %m");
                else {
                        log_link_debug(link, "Acquiring DHCPv6 lease on NDisc request");
                        r = 0;
                }
        }

        (void) ndisc_router_process_default(link, rt);
        (void) ndisc_router_process_options(link, rt);

        return r;
}