#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  line; int /*<<< orphan*/  filename; } ;
struct TYPE_8__ {scalar_t__ n_static_addresses; int /*<<< orphan*/  filename; } ;
struct TYPE_7__ {scalar_t__ family; int gateway_onlink; int /*<<< orphan*/  gw; int /*<<< orphan*/  scope; int /*<<< orphan*/  type; int /*<<< orphan*/  scope_set; int /*<<< orphan*/  table; int /*<<< orphan*/  table_set; TYPE_3__* section; } ;
typedef  TYPE_1__ Route ;
typedef  TYPE_2__ Network ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 scalar_t__ AF_UNSPEC ; 
 int EINVAL ; 
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  RTN_ANYCAST ; 
 int /*<<< orphan*/  RTN_BROADCAST ; 
 int /*<<< orphan*/  RTN_LOCAL ; 
 int /*<<< orphan*/  RTN_NAT ; 
 int /*<<< orphan*/  RT_SCOPE_HOST ; 
 int /*<<< orphan*/  RT_SCOPE_LINK ; 
 int /*<<< orphan*/  RT_TABLE_LOCAL ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 scalar_t__ in_addr_is_null (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_warning (char*,int /*<<< orphan*/ ) ; 
 int log_warning_errno (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ section_is_invalid (TYPE_3__*) ; 

int route_section_verify(Route *route, Network *network) {
        if (section_is_invalid(route->section))
                return -EINVAL;

        if (route->family == AF_UNSPEC) {
                assert(route->section);

                return log_warning_errno(SYNTHETIC_ERRNO(EINVAL),
                                         "%s: Route section without Gateway=, Destination=, Source=, "
                                         "or PreferredSource= field configured. "
                                         "Ignoring [Route] section from line %u.",
                                         route->section->filename, route->section->line);
        }

        if (route->family != AF_INET6) {
                if (!route->table_set && IN_SET(route->type, RTN_LOCAL, RTN_BROADCAST, RTN_ANYCAST, RTN_NAT))
                        route->table = RT_TABLE_LOCAL;

                if (!route->scope_set) {
                        if (IN_SET(route->type, RTN_LOCAL, RTN_NAT))
                                route->scope = RT_SCOPE_HOST;
                        else if (IN_SET(route->type, RTN_BROADCAST, RTN_ANYCAST))
                                route->scope = RT_SCOPE_LINK;
                }
        }

        if (network->n_static_addresses == 0 &&
            in_addr_is_null(route->family, &route->gw) == 0 &&
            route->gateway_onlink < 0) {
                log_warning("%s: Gateway= without static address configured. "
                            "Enabling GatewayOnLink= option.",
                            network->filename);
                route->gateway_onlink = true;
        }

        return 0;
}