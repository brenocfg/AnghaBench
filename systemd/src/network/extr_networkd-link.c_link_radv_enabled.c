#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* network; } ;
struct TYPE_6__ {scalar_t__ router_prefix_delegation; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 scalar_t__ RADV_PREFIX_DELEGATION_NONE ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  link_ipv6ll_enabled (TYPE_2__*) ; 

__attribute__((used)) static bool link_radv_enabled(Link *link) {
        assert(link);

        if (!link_ipv6ll_enabled(link))
                return false;

        return link->network->router_prefix_delegation != RADV_PREFIX_DELEGATION_NONE;
}