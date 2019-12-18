#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ protocol; } ;
typedef  TYPE_1__ DnsScope ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int dns_name_is_single_label (char const*) ; 

bool dns_scope_name_needs_search_domain(DnsScope *s, const char *name) {
        assert(s);

        if (s->protocol != DNS_PROTOCOL_DNS)
                return false;

        return dns_name_is_single_label(name);
}