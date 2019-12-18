#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  sender; int /*<<< orphan*/  family; } ;
struct TYPE_9__ {TYPE_6__* received; int /*<<< orphan*/  answer_nsec_ttl; int /*<<< orphan*/  answer_authenticated; int /*<<< orphan*/  answer; int /*<<< orphan*/  answer_rcode; int /*<<< orphan*/  key; TYPE_2__* scope; } ;
struct TYPE_8__ {TYPE_1__* manager; int /*<<< orphan*/  cache; int /*<<< orphan*/  protocol; } ;
struct TYPE_7__ {scalar_t__ enable_cache; } ;
typedef  TYPE_3__ DnsTransaction ;

/* Variables and functions */
 scalar_t__ DNS_CACHE_MODE_NO ; 
 int /*<<< orphan*/  DNS_PACKET_SHALL_CACHE (TYPE_6__*) ; 
 int /*<<< orphan*/  DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  DNS_PROTOCOL_LLMNR ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  dns_cache_put (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void dns_transaction_cache_answer(DnsTransaction *t) {
        assert(t);

        /* For mDNS we cache whenever we get the packet, rather than
         * in each transaction. */
        if (!IN_SET(t->scope->protocol, DNS_PROTOCOL_DNS, DNS_PROTOCOL_LLMNR))
                return;

        /* Caching disabled? */
        if (t->scope->manager->enable_cache == DNS_CACHE_MODE_NO)
                return;

        /* We never cache if this packet is from the local host, under
         * the assumption that a locally running DNS server would
         * cache this anyway, and probably knows better when to flush
         * the cache then we could. */
        if (!DNS_PACKET_SHALL_CACHE(t->received))
                return;

        dns_cache_put(&t->scope->cache,
                      t->scope->manager->enable_cache,
                      t->key,
                      t->answer_rcode,
                      t->answer,
                      t->answer_authenticated,
                      t->answer_nsec_ttl,
                      0,
                      t->received->family,
                      &t->received->sender);
}