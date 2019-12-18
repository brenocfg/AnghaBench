#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* manager; TYPE_1__* network; } ;
struct TYPE_6__ {int /*<<< orphan*/  dhcp4_prefix_root_cannot_set_table; } ;
struct TYPE_5__ {scalar_t__ dhcp_route_table; scalar_t__ dhcp_route_table_set; } ;
typedef  TYPE_3__ Link ;

/* Variables and functions */
 scalar_t__ RT_TABLE_MAIN ; 

__attribute__((used)) static bool link_noprefixroute(Link *link) {
        return link->network->dhcp_route_table_set &&
                link->network->dhcp_route_table != RT_TABLE_MAIN &&
                !link->manager->dhcp4_prefix_root_cannot_set_table;
}