#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {char* where; int directory_mode; int /*<<< orphan*/  timeout_idle_usec; int /*<<< orphan*/  result; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  FILE ;
typedef  TYPE_1__ Automount ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int FORMAT_TIMESPAN_MAX ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 char* automount_result_to_string (int /*<<< orphan*/ ) ; 
 char* automount_state_to_string (int /*<<< orphan*/ ) ; 
 char* format_timespan (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,char*,char const*,char*,char const*,char*,char const*,int,char const*,char*) ; 

__attribute__((used)) static void automount_dump(Unit *u, FILE *f, const char *prefix) {
        char time_string[FORMAT_TIMESPAN_MAX];
        Automount *a = AUTOMOUNT(u);

        assert(a);

        fprintf(f,
                "%sAutomount State: %s\n"
                "%sResult: %s\n"
                "%sWhere: %s\n"
                "%sDirectoryMode: %04o\n"
                "%sTimeoutIdleUSec: %s\n",
                prefix, automount_state_to_string(a->state),
                prefix, automount_result_to_string(a->result),
                prefix, a->where,
                prefix, a->directory_mode,
                prefix, format_timespan(time_string, FORMAT_TIMESPAN_MAX, a->timeout_idle_usec, USEC_PER_SEC));
}