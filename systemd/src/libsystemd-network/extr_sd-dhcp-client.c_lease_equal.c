#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ address; scalar_t__ subnet_mask; scalar_t__ router_size; TYPE_1__* router; } ;
typedef  TYPE_2__ sd_dhcp_lease ;
struct TYPE_5__ {scalar_t__ s_addr; } ;

/* Variables and functions */

__attribute__((used)) static bool lease_equal(const sd_dhcp_lease *a, const sd_dhcp_lease *b) {
        if (a->address != b->address)
                return false;

        if (a->subnet_mask != b->subnet_mask)
                return false;

        if (a->router_size != b->router_size)
                return false;

        for (size_t i = 0; i < a->router_size; i++)
                if (a->router[i].s_addr != b->router[i].s_addr)
                        return false;

        return true;
}