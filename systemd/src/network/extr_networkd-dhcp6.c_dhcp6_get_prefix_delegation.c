#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* network; } ;
struct TYPE_4__ {int /*<<< orphan*/  router_prefix_delegation; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADV_PREFIX_DELEGATION_BOTH ; 
 int /*<<< orphan*/  RADV_PREFIX_DELEGATION_DHCP6 ; 

__attribute__((used)) static bool dhcp6_get_prefix_delegation(Link *link) {
        if (!link->network)
                return false;

        return IN_SET(link->network->router_prefix_delegation,
                      RADV_PREFIX_DELEGATION_DHCP6,
                      RADV_PREFIX_DELEGATION_BOTH);
}