#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_9__ {int /*<<< orphan*/  ipv6ll_address; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  in_addr_is_null (int /*<<< orphan*/ ,union in_addr_union const*) ; 
 int link_acquire_ipv4_conf (TYPE_1__*) ; 
 int link_acquire_ipv6_conf (TYPE_1__*) ; 
 scalar_t__ link_lldp_emit_enabled (TYPE_1__*) ; 
 int link_lldp_emit_start (TYPE_1__*) ; 
 int log_link_warning_errno (TYPE_1__*,int,char*) ; 

__attribute__((used)) static int link_acquire_conf(Link *link) {
        int r;

        assert(link);

        r = link_acquire_ipv4_conf(link);
        if (r < 0)
                return r;

        if (!in_addr_is_null(AF_INET6, (const union in_addr_union*) &link->ipv6ll_address)) {
                r = link_acquire_ipv6_conf(link);
                if (r < 0)
                        return r;
        }

        if (link_lldp_emit_enabled(link)) {
                r = link_lldp_emit_start(link);
                if (r < 0)
                        return log_link_warning_errno(link, r, "Failed to start LLDP transmission: %m");
        }

        return 0;
}