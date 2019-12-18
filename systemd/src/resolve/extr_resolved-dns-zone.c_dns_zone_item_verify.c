#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  rr; } ;
typedef  TYPE_1__ DnsZoneItem ;

/* Variables and functions */
 scalar_t__ DNS_ZONE_ITEM_ESTABLISHED ; 
 scalar_t__ DNS_ZONE_ITEM_VERIFYING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_resource_record_to_string (int /*<<< orphan*/ ) ; 
 int dns_zone_item_probe_start (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_zone_item_verify(DnsZoneItem *i) {
        int r;

        assert(i);

        if (i->state != DNS_ZONE_ITEM_ESTABLISHED)
                return 0;

        log_debug("Verifying RR %s", strna(dns_resource_record_to_string(i->rr)));

        i->state = DNS_ZONE_ITEM_VERIFYING;
        r = dns_zone_item_probe_start(i);
        if (r < 0) {
                log_error_errno(r, "Failed to start probing for verifying RR: %m");
                i->state = DNS_ZONE_ITEM_ESTABLISHED;
                return r;
        }

        return 0;
}