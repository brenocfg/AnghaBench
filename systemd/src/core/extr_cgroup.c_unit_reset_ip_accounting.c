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
struct TYPE_4__ {scalar_t__ ip_accounting_ingress_map_fd; scalar_t__ ip_accounting_egress_map_fd; int /*<<< orphan*/  ip_accounting_extra; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int bpf_firewall_reset_accounting (scalar_t__) ; 
 int /*<<< orphan*/  zero (int /*<<< orphan*/ ) ; 

int unit_reset_ip_accounting(Unit *u) {
        int r = 0, q = 0;

        assert(u);

        if (u->ip_accounting_ingress_map_fd >= 0)
                r = bpf_firewall_reset_accounting(u->ip_accounting_ingress_map_fd);

        if (u->ip_accounting_egress_map_fd >= 0)
                q = bpf_firewall_reset_accounting(u->ip_accounting_egress_map_fd);

        zero(u->ip_accounting_extra);

        return r < 0 ? r : q;
}