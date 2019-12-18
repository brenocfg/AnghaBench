#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  buf_runtime ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_10__ {int /*<<< orphan*/  kill_context; int /*<<< orphan*/  runtime_max_usec; int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ Scope ;
typedef  TYPE_1__ FILE ;

/* Variables and functions */
 int FORMAT_TIMESPAN_MAX ; 
 TYPE_1__* SCOPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cgroup_context_dump (int /*<<< orphan*/ ,TYPE_1__*,char const*) ; 
 char* format_timespan (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (TYPE_1__*,char*,char const*,char*,char const*,char*,char const*,char*) ; 
 int /*<<< orphan*/  kill_context_dump (int /*<<< orphan*/ *,TYPE_1__*,char const*) ; 
 char* scope_result_to_string (int /*<<< orphan*/ ) ; 
 char* scope_state_to_string (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scope_dump(Unit *u, FILE *f, const char *prefix) {
        Scope *s = SCOPE(u);
        char buf_runtime[FORMAT_TIMESPAN_MAX];

        assert(s);
        assert(f);

        fprintf(f,
                "%sScope State: %s\n"
                "%sResult: %s\n"
                "%sRuntimeMaxSec: %s\n",
                prefix, scope_state_to_string(s->state),
                prefix, scope_result_to_string(s->result),
                prefix, format_timespan(buf_runtime, sizeof(buf_runtime), s->runtime_max_usec, USEC_PER_SEC));

        cgroup_context_dump(UNIT(s), f, prefix);
        kill_context_dump(&s->kill_context, f, prefix);
}