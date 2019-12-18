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
typedef  int /*<<< orphan*/  DnsZoneItem ;
typedef  int /*<<< orphan*/  DnsZone ;
typedef  int /*<<< orphan*/  DnsResourceRecord ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dns_zone_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_zone_item_remove_and_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void dns_zone_remove_rr(DnsZone *z, DnsResourceRecord *rr) {
        DnsZoneItem *i;

        assert(z);
        assert(rr);

        i = dns_zone_get(z, rr);
        if (i)
                dns_zone_item_remove_and_free(z, i);
}