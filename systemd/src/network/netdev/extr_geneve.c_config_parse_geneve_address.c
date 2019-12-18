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
struct TYPE_2__ {int remote_family; } ;
typedef  TYPE_1__ Geneve ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int in_addr_from_string_auto (char const*,int*,union in_addr_union*) ; 
 int in_addr_is_multicast (int,union in_addr_union*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 

int config_parse_geneve_address(const char *unit,
                                const char *filename,
                                unsigned line,
                                const char *section,
                                unsigned section_line,
                                const char *lvalue,
                                int ltype,
                                const char *rvalue,
                                void *data,
                                void *userdata) {
        Geneve *v = userdata;
        union in_addr_union *addr = data, buffer;
        int r, f;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = in_addr_from_string_auto(rvalue, &f, &buffer);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "geneve '%s' address is invalid, ignoring assignment: %s", lvalue, rvalue);
                return 0;
        }

        r = in_addr_is_multicast(f, &buffer);
        if (r > 0) {
                log_syntax(unit, LOG_ERR, filename, line, 0, "geneve invalid multicast '%s' address, ignoring assignment: %s", lvalue, rvalue);
                return 0;
        }

        v->remote_family = f;
        *addr = buffer;

        return 0;
}