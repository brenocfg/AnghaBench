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
struct TYPE_2__ {int local_family; int peer_family; } ;
typedef  TYPE_1__ FouTunnel ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int in_addr_from_string_auto (char const*,int*,union in_addr_union*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_fou_tunnel_address(
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

        union in_addr_union *addr = data;
        FouTunnel *t = userdata;
        int r, *f;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (streq(lvalue, "Local"))
                f = &t->local_family;
        else
                f = &t->peer_family;

        r = in_addr_from_string_auto(rvalue, f, addr);
        if (r < 0)
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Foo over UDP tunnel '%s' address is invalid, ignoring assignment: %s",
                           lvalue, rvalue);

        return 0;
}