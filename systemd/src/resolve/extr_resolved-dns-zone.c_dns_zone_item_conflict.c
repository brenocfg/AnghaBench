#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  key; } ;
struct TYPE_8__ {TYPE_1__* scope; TYPE_5__* rr; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_2__ DnsZoneItem ;

/* Variables and functions */
 int /*<<< orphan*/  DNS_ZONE_ITEM_ESTABLISHED ; 
 int /*<<< orphan*/  DNS_ZONE_ITEM_PROBING ; 
 int /*<<< orphan*/  DNS_ZONE_ITEM_VERIFYING ; 
 int /*<<< orphan*/  DNS_ZONE_ITEM_WITHDRAWN ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_resource_key_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_record_to_string (TYPE_5__*) ; 
 int /*<<< orphan*/  dns_zone_item_probe_stop (TYPE_2__*) ; 
 int /*<<< orphan*/  dnssd_signal_conflict (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ manager_is_own_hostname (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  manager_next_hostname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strna (int /*<<< orphan*/ ) ; 

void dns_zone_item_conflict(DnsZoneItem *i) {
        assert(i);

        if (!IN_SET(i->state, DNS_ZONE_ITEM_PROBING, DNS_ZONE_ITEM_VERIFYING, DNS_ZONE_ITEM_ESTABLISHED))
                return;

        log_info("Detected conflict on %s", strna(dns_resource_record_to_string(i->rr)));

        dns_zone_item_probe_stop(i);

        /* Withdraw the conflict item */
        i->state = DNS_ZONE_ITEM_WITHDRAWN;

        dnssd_signal_conflict(i->scope->manager, dns_resource_key_name(i->rr->key));

        /* Maybe change the hostname */
        if (manager_is_own_hostname(i->scope->manager, dns_resource_key_name(i->rr->key)) > 0)
                manager_next_hostname(i->scope->manager);
}