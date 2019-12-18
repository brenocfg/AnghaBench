#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ether_arp {int /*<<< orphan*/  address; int /*<<< orphan*/  arp_spa; } ;
typedef  struct ether_arp sd_ipv4acd ;

/* Variables and functions */
 int /*<<< orphan*/  assert (struct ether_arp*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static bool ipv4acd_arp_conflict(sd_ipv4acd *acd, struct ether_arp *arp) {
        assert(acd);
        assert(arp);

        /* see the BPF */
        if (memcmp(arp->arp_spa, &acd->address, sizeof(acd->address)) == 0)
                return true;

        /* the TPA matched instead of the SPA, this is not a conflict */
        return false;
}