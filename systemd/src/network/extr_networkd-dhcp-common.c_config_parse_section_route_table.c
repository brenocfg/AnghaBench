#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_2__ {int dhcp_route_table_set; int ipv6_accept_ra_route_table_set; void* ipv6_accept_ra_route_table; void* dhcp_route_table; } ;
typedef  TYPE_1__ Network ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ STRPTR_IN_SET (char const*,char*,char*) ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int safe_atou32 (char const*,void**) ; 

int config_parse_section_route_table(
                const char *unit,
                const char *filename,
                unsigned line,
                const char *section,
                unsigned section_line,
                const char *lvalue,
                int ltype,
                const char *rvalue,
                void *data,
                void *userdata) {

        Network *network = data;
        uint32_t rt;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = safe_atou32(rvalue, &rt);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Failed to parse RouteTable=%s, ignoring assignment: %m", rvalue);
                return 0;
        }

        if (STRPTR_IN_SET(section, "DHCP", "DHCPv4")) {
                network->dhcp_route_table = rt;
                network->dhcp_route_table_set = true;
        } else { /* section is IPv6AcceptRA */
                network->ipv6_accept_ra_route_table = rt;
                network->ipv6_accept_ra_route_table_set = true;
        }

        return 0;
}