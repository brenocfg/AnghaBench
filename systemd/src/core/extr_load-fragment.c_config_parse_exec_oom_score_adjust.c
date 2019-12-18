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
struct TYPE_2__ {int oom_score_adjust_set; int oom_score_adjust; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int ERANGE ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 
 int parse_oom_score_adjust (char const*,int*) ; 

int config_parse_exec_oom_score_adjust(
                const char* unit,
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
        int oa, r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                c->oom_score_adjust_set = false;
                return 0;
        }

        r = parse_oom_score_adjust(rvalue, &oa);
        if (r < 0) {
                if (r == -ERANGE)
                        log_syntax(unit, LOG_ERR, filename, line, r, "OOM score adjust value out of range, ignoring: %s", rvalue);
                else
                        log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse the OOM score adjust value '%s', ignoring: %m", rvalue);
                return 0;
        }

        c->oom_score_adjust = oa;
        c->oom_score_adjust_set = true;

        return 0;
}