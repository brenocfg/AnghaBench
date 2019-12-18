#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  key; } ;
struct TYPE_6__ {TYPE_4__* rr; TYPE_1__* scope; } ;
struct TYPE_5__ {scalar_t__ protocol; } ;
typedef  TYPE_2__ DnsZoneItem ;
typedef  int DnsAnswerFlags ;
typedef  int /*<<< orphan*/  DnsAnswer ;

/* Variables and functions */
 int DNS_ANSWER_AUTHENTICATED ; 
 int DNS_ANSWER_CACHE_FLUSH ; 
 scalar_t__ DNS_PROTOCOL_MDNS ; 
 int dns_answer_add (int /*<<< orphan*/ *,TYPE_4__*,int,int) ; 
 int /*<<< orphan*/  dns_resource_key_is_dnssd_ptr (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dns_zone_add_authenticated_answer(DnsAnswer *a, DnsZoneItem *i, int ifindex) {
        DnsAnswerFlags flags;

        /* From RFC 6762, Section 10.2
         * "They (the rules about when to set the cache-flush bit) apply to
         * startup announcements as described in Section 8.3, "Announcing",
         * and to responses generated as a result of receiving query messages."
         * So, set the cache-flush bit for mDNS answers except for DNS-SD
         * service enumeration PTRs described in RFC 6763, Section 4.1. */
        if (i->scope->protocol == DNS_PROTOCOL_MDNS &&
            !dns_resource_key_is_dnssd_ptr(i->rr->key))
                flags = DNS_ANSWER_AUTHENTICATED|DNS_ANSWER_CACHE_FLUSH;
        else
                flags = DNS_ANSWER_AUTHENTICATED;

        return dns_answer_add(a, i->rr, ifindex, flags);
}