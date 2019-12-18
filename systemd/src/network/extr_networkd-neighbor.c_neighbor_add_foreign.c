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
typedef  union lladdr_union {int dummy; } lladdr_union ;
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_4__ {int /*<<< orphan*/  neighbors_foreign; } ;
typedef  int /*<<< orphan*/  Neighbor ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int neighbor_add_internal (TYPE_1__*,int /*<<< orphan*/ *,int,union in_addr_union const*,union lladdr_union const*,size_t,int /*<<< orphan*/ **) ; 

int neighbor_add_foreign(Link *link, int family, const union in_addr_union *addr, const union lladdr_union *lladdr, size_t lladdr_size, Neighbor **ret) {
        return neighbor_add_internal(link, &link->neighbors_foreign, family, addr, lladdr, lladdr_size, ret);
}