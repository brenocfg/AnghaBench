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
struct TYPE_6__ {scalar_t__ class; scalar_t__ type; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DNS_TYPE_SOA ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 int dns_name_endswith (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 

int dns_resource_key_match_soa(const DnsResourceKey *key, const DnsResourceKey *soa) {
        assert(soa);
        assert(key);

        /* Checks whether 'soa' is a SOA record for the specified key. */

        if (soa->class != key->class)
                return 0;

        if (soa->type != DNS_TYPE_SOA)
                return 0;

        return dns_name_endswith(dns_resource_key_name(key), dns_resource_key_name(soa));
}