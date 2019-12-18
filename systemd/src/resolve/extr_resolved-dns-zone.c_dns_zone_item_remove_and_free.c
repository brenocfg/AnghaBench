#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  by_name; int /*<<< orphan*/  by_key; } ;
struct TYPE_13__ {TYPE_1__* rr; } ;
struct TYPE_12__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ DnsZoneItem ;
typedef  TYPE_3__ DnsZone ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  by_key ; 
 int /*<<< orphan*/  by_name ; 
 int /*<<< orphan*/  dns_resource_key_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_zone_item_free (TYPE_2__*) ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hashmap_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void dns_zone_item_remove_and_free(DnsZone *z, DnsZoneItem *i) {
        DnsZoneItem *first;

        assert(z);

        if (!i)
                return;

        first = hashmap_get(z->by_key, i->rr->key);
        LIST_REMOVE(by_key, first, i);
        if (first)
                assert_se(hashmap_replace(z->by_key, first->rr->key, first) >= 0);
        else
                hashmap_remove(z->by_key, i->rr->key);

        first = hashmap_get(z->by_name, dns_resource_key_name(i->rr->key));
        LIST_REMOVE(by_name, first, i);
        if (first)
                assert_se(hashmap_replace(z->by_name, dns_resource_key_name(first->rr->key), first) >= 0);
        else
                hashmap_remove(z->by_name, dns_resource_key_name(i->rr->key));

        dns_zone_item_free(i);
}