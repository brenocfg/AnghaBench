#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {TYPE_2__* scope; TYPE_1__* query; } ;
struct TYPE_7__ {scalar_t__ protocol; int /*<<< orphan*/  manager; scalar_t__ link; } ;
struct TYPE_6__ {int /*<<< orphan*/  suppress_unroutable_family; } ;
typedef  TYPE_3__ DnsQueryCandidate ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int dns_type_to_af (int /*<<< orphan*/ ) ; 
 int link_relevant (scalar_t__,int,int) ; 
 int manager_routable (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool dns_query_candidate_is_routable(DnsQueryCandidate *c, uint16_t type) {
        int family;

        assert(c);

        /* Checks whether the specified RR type matches an address family that is routable on the link(s) the scope of
         * this candidate belongs to. Specifically, whether there's a routable IPv4 address on it if we query an A RR,
         * or a routable IPv6 address if we query an AAAA RR. */

        if (!c->query->suppress_unroutable_family)
                return true;

        if (c->scope->protocol != DNS_PROTOCOL_DNS)
                return true;

        family = dns_type_to_af(type);
        if (family < 0)
                return true;

        if (c->scope->link)
                return link_relevant(c->scope->link, family, false);
        else
                return manager_routable(c->scope->manager, family);
}