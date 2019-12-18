#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ class; } ;
struct TYPE_7__ {TYPE_5__* key; } ;
typedef  TYPE_1__ DnsTransaction ;
typedef  TYPE_1__ DnsResourceRecord ;

/* Variables and functions */
 scalar_t__ DNS_CLASS_IN ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ dns_name_is_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_5__*) ; 

__attribute__((used)) static int dns_transaction_known_signed(DnsTransaction *t, DnsResourceRecord *rr) {
        assert(t);
        assert(rr);

        /* We know that the root domain is signed, hence if it appears
         * not to be signed, there's a problem with the DNS server */

        return rr->key->class == DNS_CLASS_IN &&
                dns_name_is_root(dns_resource_key_name(rr->key));
}