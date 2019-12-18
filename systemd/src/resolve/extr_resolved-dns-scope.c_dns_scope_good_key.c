#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ class; scalar_t__ protocol; int family; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ const DnsScope ;
typedef  TYPE_1__ DnsResourceKey ;

/* Variables and functions */
 scalar_t__ DNS_CLASS_IN ; 
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_1__ const*) ; 
 scalar_t__ dns_name_is_root (int /*<<< orphan*/ ) ; 
 scalar_t__ dns_name_is_single_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dns_resource_key_is_address (TYPE_1__ const*) ; 
 int /*<<< orphan*/  dns_resource_key_name (TYPE_1__ const*) ; 
 int dns_type_to_af (int /*<<< orphan*/ ) ; 

bool dns_scope_good_key(DnsScope *s, const DnsResourceKey *key) {
        int key_family;

        assert(s);
        assert(key);

        /* Check if it makes sense to resolve the specified key on
         * this scope. Note that this call assumes as fully qualified
         * name, i.e. the search suffixes already appended. */

        if (key->class != DNS_CLASS_IN)
                return false;

        if (s->protocol == DNS_PROTOCOL_DNS) {

                /* On classic DNS, looking up non-address RRs is always
                 * fine. (Specifically, we want to permit looking up
                 * DNSKEY and DS records on the root and top-level
                 * domains.) */
                if (!dns_resource_key_is_address(key))
                        return true;

                /* However, we refuse to look up A and AAAA RRs on the
                 * root and single-label domains, under the assumption
                 * that those should be resolved via LLMNR or search
                 * path only, and should not be leaked onto the
                 * internet. */
                return !(dns_name_is_single_label(dns_resource_key_name(key)) ||
                         dns_name_is_root(dns_resource_key_name(key)));
        }

        /* On mDNS and LLMNR, send A and AAAA queries only on the
         * respective scopes */

        key_family = dns_type_to_af(key->type);
        if (key_family < 0)
                return true;

        return key_family == s->family;
}