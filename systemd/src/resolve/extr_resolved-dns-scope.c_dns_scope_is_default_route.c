#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ protocol; TYPE_1__* link; } ;
struct TYPE_6__ {scalar_t__ default_route; } ;
typedef  TYPE_2__ DnsScope ;

/* Variables and functions */
 scalar_t__ DNS_PROTOCOL_DNS ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dns_scope_has_route_only_domains (TYPE_2__*) ; 

bool dns_scope_is_default_route(DnsScope *scope) {
        assert(scope);

        /* Only use DNS scopes as default routes */
        if (scope->protocol != DNS_PROTOCOL_DNS)
                return false;

        /* The global DNS scope is always suitable as default route */
        if (!scope->link)
                return true;

        /* Honour whatever is explicitly configured. This is really the best approach, and trumps any
         * automatic logic. */
        if (scope->link->default_route >= 0)
                return scope->link->default_route;

        /* Otherwise check if we have any route-only domains, as a sensible heuristic: if so, let's not
         * volunteer as default route. */
        return !dns_scope_has_route_only_domains(scope);
}