#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ ttl; int enabled_capabilities; int capability_mask; scalar_t__ has_capabilities; int /*<<< orphan*/  source_address; int /*<<< orphan*/  filter_address; } ;
typedef  TYPE_1__ sd_lldp_neighbor ;
typedef  TYPE_1__ sd_lldp ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ ether_addr_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ether_addr_is_null (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool lldp_keep_neighbor(sd_lldp *lldp, sd_lldp_neighbor *n) {
        assert(lldp);
        assert(n);

        /* Don't keep data with a zero TTL */
        if (n->ttl <= 0)
                return false;

        /* Filter out data from the filter address */
        if (!ether_addr_is_null(&lldp->filter_address) &&
            ether_addr_equal(&lldp->filter_address, &n->source_address))
                return false;

        /* Only add if the neighbor has a capability we are interested in. Note that we also store all neighbors with
         * no caps field set. */
        if (n->has_capabilities &&
            (n->enabled_capabilities & lldp->capability_mask) == 0)
                return false;

        /* Keep everything else */
        return true;
}