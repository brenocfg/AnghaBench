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
typedef  union in_addr_union {int dummy; } in_addr_union ;
struct TYPE_2__ {scalar_t__ family; scalar_t__ local_address_type; int /*<<< orphan*/  local; int /*<<< orphan*/  remote; } ;
typedef  TYPE_1__ L2tpTunnel ;
typedef  scalar_t__ L2tpLocalAddressType ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int /*<<< orphan*/  IN_ADDR_NULL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 scalar_t__ NETDEV_L2TP_LOCAL_ADDRESS_AUTO ; 
 int /*<<< orphan*/  assert (void*) ; 
 int in_addr_from_string (scalar_t__,char const*,union in_addr_union*) ; 
 int in_addr_from_string_auto (char const*,scalar_t__*,union in_addr_union*) ; 
 scalar_t__ in_addr_is_null (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ isempty (char const*) ; 
 scalar_t__ l2tp_local_address_type_from_string (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_l2tp_tunnel_address(
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

        L2tpTunnel *t = userdata;
        union in_addr_union *addr = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (streq(lvalue, "Local")) {
                L2tpLocalAddressType addr_type;

                if (isempty(rvalue))
                        addr_type = NETDEV_L2TP_LOCAL_ADDRESS_AUTO;
                else
                        addr_type = l2tp_local_address_type_from_string(rvalue);

                if (addr_type >= 0) {
                        if (in_addr_is_null(t->family, &t->remote) != 0)
                                /* If Remote= is not specified yet, then also clear family. */
                                t->family = AF_UNSPEC;

                        t->local = IN_ADDR_NULL;
                        t->local_address_type = addr_type;

                        return 0;
                }
        }

        if (t->family == AF_UNSPEC)
                r = in_addr_from_string_auto(rvalue, &t->family, addr);
        else
                r = in_addr_from_string(t->family, rvalue, addr);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Invalid L2TP Tunnel address specified in %s='%s', ignoring assignment: %m", lvalue, rvalue);
                return 0;
        }

        return 0;
}