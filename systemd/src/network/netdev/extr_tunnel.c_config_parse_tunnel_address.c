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
struct TYPE_2__ {int family; int /*<<< orphan*/  remote; int /*<<< orphan*/  local; } ;
typedef  TYPE_1__ Tunnel ;

/* Variables and functions */
 int AF_UNSPEC ; 
 union in_addr_union IN_ADDR_NULL ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int in_addr_from_string_auto (char const*,int*,union in_addr_union*) ; 
 scalar_t__ in_addr_is_null (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_tunnel_address(const char *unit,
                                const char *filename,
                                unsigned line,
                                const char *section,
                                unsigned section_line,
                                const char *lvalue,
                                int ltype,
                                const char *rvalue,
                                void *data,
                                void *userdata) {
        Tunnel *t = userdata;
        union in_addr_union *addr = data, buffer;
        int r, f;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        /* This is used to parse addresses on both local and remote ends of the tunnel.
         * Address families must match.
         *
         * "any" is a special value which means that the address is unspecified.
         */

        if (streq(rvalue, "any")) {
                *addr = IN_ADDR_NULL;

                /* As a special case, if both the local and remote addresses are
                 * unspecified, also clear the address family.
                 */
                if (t->family != AF_UNSPEC &&
                    in_addr_is_null(t->family, &t->local) != 0 &&
                    in_addr_is_null(t->family, &t->remote) != 0)
                        t->family = AF_UNSPEC;
                return 0;
        }

        r = in_addr_from_string_auto(rvalue, &f, &buffer);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Tunnel address \"%s\" invalid, ignoring assignment: %m", rvalue);
                return 0;
        }

        if (t->family != AF_UNSPEC && t->family != f) {
                log_syntax(unit, LOG_ERR, filename, line, 0,
                           "Tunnel addresses incompatible, ignoring assignment: %s", rvalue);
                return 0;
        }

        t->family = f;
        *addr = buffer;
        return 0;
}