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
struct TYPE_2__ {int /*<<< orphan*/  network_veth_extra; } ;
typedef  TYPE_1__ Settings ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int veth_extra_parse (int /*<<< orphan*/ *,char const*) ; 

int config_parse_veth_extra(
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

        Settings *settings = data;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);

        r = veth_extra_parse(&settings->network_veth_extra, rvalue);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Invalid extra virtual Ethernet link specification %s: %m", rvalue);
                return 0;
        }

        return 0;
}