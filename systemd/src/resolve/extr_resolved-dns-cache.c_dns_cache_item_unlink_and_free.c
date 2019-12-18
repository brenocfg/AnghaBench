#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  by_expiry; int /*<<< orphan*/  by_key; } ;
struct TYPE_12__ {int /*<<< orphan*/  prioq_idx; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ DnsCacheItem ;
typedef  TYPE_2__ DnsCache ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  by_key ; 
 int /*<<< orphan*/  dns_cache_item_free (TYPE_1__*) ; 
 TYPE_1__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ hashmap_replace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  prioq_remove (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dns_cache_item_unlink_and_free(DnsCache *c, DnsCacheItem *i) {
        DnsCacheItem *first;

        assert(c);

        if (!i)
                return;

        first = hashmap_get(c->by_key, i->key);
        LIST_REMOVE(by_key, first, i);

        if (first)
                assert_se(hashmap_replace(c->by_key, first->key, first) >= 0);
        else
                hashmap_remove(c->by_key, i->key);

        prioq_remove(c->by_expiry, i, &i->prioq_idx);

        dns_cache_item_free(i);
}