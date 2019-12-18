#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  notify_zone_items_done; int /*<<< orphan*/  notify_zone_items; } ;
struct TYPE_8__ {int /*<<< orphan*/  probe_transaction; } ;
typedef  TYPE_1__ DnsZoneItem ;
typedef  TYPE_2__ DnsTransaction ;

/* Variables and functions */
 TYPE_2__* TAKE_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dns_transaction_gc (TYPE_2__*) ; 
 int /*<<< orphan*/  set_remove (int /*<<< orphan*/ ,TYPE_1__*) ; 

void dns_zone_item_probe_stop(DnsZoneItem *i) {
        DnsTransaction *t;
        assert(i);

        if (!i->probe_transaction)
                return;

        t = TAKE_PTR(i->probe_transaction);

        set_remove(t->notify_zone_items, i);
        set_remove(t->notify_zone_items_done, i);
        dns_transaction_gc(t);
}