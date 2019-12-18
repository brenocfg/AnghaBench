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
struct TYPE_2__ {int inherit; unsigned int ttl; } ;
typedef  TYPE_1__ VxLan ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int safe_atou (char const*,unsigned int*) ; 
 scalar_t__ streq (char const*,char*) ; 

int config_parse_vxlan_ttl(const char *unit,
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
        unsigned f;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (streq(rvalue, "inherit"))
                v->inherit = true;
        else {
                r = safe_atou(rvalue, &f);
                if (r < 0) {
                        log_syntax(unit, LOG_ERR, filename, line, r,
                                   "Failed to parse VXLAN TTL '%s', ignoring assignment: %m", rvalue);
                        return 0;
                }

                if (f > 255) {
                        log_syntax(unit, LOG_ERR, filename, line, 0,
                                   "Invalid VXLAN TTL '%s'. TTL must be <= 255. Ignoring assignment.", rvalue);
                        return 0;
                }

                v->ttl = f;
        }

        return 0;
}