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
struct TYPE_2__ {int /*<<< orphan*/  cpu_set; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  assert (void*) ; 
 int parse_cpu_set_extend (char const*,int /*<<< orphan*/ *,int,char const*,char const*,unsigned int,char const*) ; 

int config_parse_exec_cpu_affinity(const char *unit,
                                   const char *filename,
                                   unsigned line,
                                   const char *section,
                                   unsigned section_line,
                                   const char *lvalue,
                                   int ltype,
                                   const char *rvalue,
                                   void *data,
                                   void *userdata) {

        ExecContext *c = data;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        return parse_cpu_set_extend(rvalue, &c->cpu_set, true, unit, filename, line, lvalue);
}