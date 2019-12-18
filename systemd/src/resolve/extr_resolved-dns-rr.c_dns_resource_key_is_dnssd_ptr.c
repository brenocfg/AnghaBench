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
struct TYPE_5__ {scalar_t__ type; } ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DNS_TYPE_PTR ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ dns_name_endswith (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 

bool dns_resource_key_is_dnssd_ptr(const DnsResourceKey *key) {
        assert(key);

        /* Check if this is a PTR resource key used in
           Service Instance Enumeration as described in RFC6763 p4.1. */

        if (key->type != DNS_TYPE_PTR)
                return false;

        return dns_name_endswith(dns_resource_key_name(key), "_tcp.local") ||
                dns_name_endswith(dns_resource_key_name(key), "_udp.local");
}