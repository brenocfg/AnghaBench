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
struct TYPE_4__ {int mcast_querier; int mcast_snooping; int vlan_filtering; int stp; void* ageing_time; void* forward_delay; int /*<<< orphan*/  default_pvid; } ;
typedef  int /*<<< orphan*/  NetDev ;
typedef  TYPE_1__ Bridge ;

/* Variables and functions */
 TYPE_1__* BRIDGE (int /*<<< orphan*/ *) ; 
 void* USEC_INFINITY ; 
 int /*<<< orphan*/  VLANID_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 

__attribute__((used)) static void bridge_init(NetDev *n) {
        Bridge *b;

        b = BRIDGE(n);

        assert(b);

        b->mcast_querier = -1;
        b->mcast_snooping = -1;
        b->vlan_filtering = -1;
        b->stp = -1;
        b->default_pvid = VLANID_INVALID;
        b->forward_delay = USEC_INFINITY;
        b->ageing_time = USEC_INFINITY;
}