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
struct TYPE_5__ {scalar_t__ protocol; } ;
typedef  TYPE_1__ DnsScope ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_LLMNR ; 
 int /*<<< orphan*/  LLMNR_MULTICAST_IPV4_ADDRESS ; 
 int /*<<< orphan*/  LLMNR_MULTICAST_IPV6_ADDRESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_scope_multicast_membership (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dns_scope_llmnr_membership(DnsScope *s, bool b) {
        assert(s);

        if (s->protocol != DNS_PROTOCOL_LLMNR)
                return 0;

        return dns_scope_multicast_membership(s, b, LLMNR_MULTICAST_IPV4_ADDRESS, LLMNR_MULTICAST_IPV6_ADDRESS);
}