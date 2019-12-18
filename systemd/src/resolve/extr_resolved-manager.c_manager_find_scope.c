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
struct TYPE_9__ {int /*<<< orphan*/ * mdns_ipv6_scope; int /*<<< orphan*/ * mdns_ipv4_scope; int /*<<< orphan*/ * llmnr_ipv6_scope; int /*<<< orphan*/ * llmnr_ipv4_scope; } ;
struct TYPE_8__ {int protocol; int /*<<< orphan*/  family; int /*<<< orphan*/  ifindex; int /*<<< orphan*/  links; } ;
typedef  TYPE_1__ Manager ;
typedef  TYPE_2__ Link ;
typedef  int /*<<< orphan*/  DnsScope ;
typedef  TYPE_1__ DnsPacket ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
#define  DNS_PROTOCOL_LLMNR 129 
#define  DNS_PROTOCOL_MDNS 128 
 int /*<<< orphan*/  INT_TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 TYPE_2__* hashmap_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

DnsScope* manager_find_scope(Manager *m, DnsPacket *p) {
        Link *l;

        assert(m);
        assert(p);

        l = hashmap_get(m->links, INT_TO_PTR(p->ifindex));
        if (!l)
                return NULL;

        switch (p->protocol) {
        case DNS_PROTOCOL_LLMNR:
                if (p->family == AF_INET)
                        return l->llmnr_ipv4_scope;
                else if (p->family == AF_INET6)
                        return l->llmnr_ipv6_scope;

                break;

        case DNS_PROTOCOL_MDNS:
                if (p->family == AF_INET)
                        return l->mdns_ipv4_scope;
                else if (p->family == AF_INET6)
                        return l->mdns_ipv6_scope;

                break;

        default:
                break;
        }

        return NULL;
}