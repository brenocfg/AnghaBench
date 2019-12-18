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
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {int smack_process_label_ignore; int /*<<< orphan*/  smack_process_label; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int ENOEXEC ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int /*<<< orphan*/  free_and_replace (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*,char*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 int unit_full_printf (int /*<<< orphan*/  const*,char const*,char**) ; 

int config_parse_exec_smack_process_label(
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

        ExecContext *c = data;
        const Unit *u = userdata;
        bool ignore;
        char *k;
        int r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                c->smack_process_label = mfree(c->smack_process_label);
                c->smack_process_label_ignore = false;
                return 0;
        }

        if (rvalue[0] == '-') {
                ignore = true;
                rvalue++;
        } else
                ignore = false;

        r = unit_full_printf(u, rvalue, &k);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r,
                           "Failed to resolve unit specifiers in '%s'%s: %m",
                           rvalue, ignore ? ", ignoring" : "");
                return ignore ? 0 : -ENOEXEC;
        }

        free_and_replace(c->smack_process_label, k);
        c->smack_process_label_ignore = ignore;

        return 0;
}