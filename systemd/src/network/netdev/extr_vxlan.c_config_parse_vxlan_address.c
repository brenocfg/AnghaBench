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
struct TYPE_2__ {int group_family; int remote_family; int local_family; } ;
typedef  TYPE_1__ VxLan ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int in_addr_from_string_auto (char const*,int*,union in_addr_union*) ; 
 int in_addr_is_multicast (int,union in_addr_union*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_vxlan_address(const char *unit,
                               const char *filename,
                               unsigned line,
                               const char *section,
                               unsigned section_line,
                               const char *lvalue,
                               int ltype,
                               const char *rvalue,
                               void *data,
                               void *userdata) {
        VxLan *v = userdata;
        union in_addr_union *addr = data, buffer;
        int r, f;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        r = in_addr_from_string_auto(rvalue, &f, &buffer);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "vxlan '%s' address is invalid, ignoring assignment: %s", lvalue, rvalue);
                return 0;
        }

        r = in_addr_is_multicast(f, &buffer);

        if (streq(lvalue, "Group")) {
                if (r <= 0) {
                        log_syntax(unit, LOG_ERR, filename, line, 0, "vxlan %s invalid multicast address, ignoring assignment: %s", lvalue, rvalue);
                        return 0;
                }

                v->group_family = f;
        } else {
                if (r > 0) {
                        log_syntax(unit, LOG_ERR, filename, line, 0, "vxlan %s cannot be a multicast address, ignoring assignment: %s", lvalue, rvalue);
                        return 0;
                }

                if (streq(lvalue, "Remote"))
                        v->remote_family = f;
                else
                        v->local_family = f;
        }

        *addr = buffer;

        return 0;
}