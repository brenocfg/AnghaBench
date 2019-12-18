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
struct TYPE_2__ {int ioprio_set; void* ioprio; } ;
typedef  TYPE_1__ ExecContext ;

/* Variables and functions */
 int /*<<< orphan*/  IOPRIO_CLASS_BE ; 
 int /*<<< orphan*/  IOPRIO_PRIO_CLASS (void*) ; 
 void* IOPRIO_PRIO_VALUE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LOG_ERR ; 
 int /*<<< orphan*/  assert (void*) ; 
 int ioprio_parse_priority (char const*,int*) ; 
 scalar_t__ isempty (char const*) ; 
 int /*<<< orphan*/  log_syntax (char const*,int /*<<< orphan*/ ,char const*,unsigned int,int,char*,char const*) ; 

int config_parse_exec_io_priority(const char *unit,
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
        int i, r;

        assert(filename);
        assert(lvalue);
        assert(rvalue);
        assert(data);

        if (isempty(rvalue)) {
                c->ioprio_set = false;
                c->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_CLASS_BE, 0);
                return 0;
        }

        r = ioprio_parse_priority(rvalue, &i);
        if (r < 0) {
                log_syntax(unit, LOG_ERR, filename, line, r, "Failed to parse IO priority, ignoring: %s", rvalue);
                return 0;
        }

        c->ioprio = IOPRIO_PRIO_VALUE(IOPRIO_PRIO_CLASS(c->ioprio), i);
        c->ioprio_set = true;

        return 0;
}