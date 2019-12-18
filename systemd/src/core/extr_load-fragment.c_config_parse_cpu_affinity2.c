#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  CPUSet ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parse_cpu_set_extend (char const*,int /*<<< orphan*/ *,int,char const*,char const*,unsigned int,char const*) ; 

int config_parse_cpu_affinity2(
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

        CPUSet *affinity = data;

        assert(affinity);

        (void) parse_cpu_set_extend(rvalue, affinity, true, unit, filename, line, lvalue);

        return 0;
}