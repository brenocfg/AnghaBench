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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  JobType ;

/* Variables and functions */
 int /*<<< orphan*/  DISABLE_WARNING_FORMAT_NONLITERAL ; 
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB_START ; 
 int /*<<< orphan*/  JOB_STOP ; 
 int /*<<< orphan*/  REENABLE_WARNING ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 char* job_get_begin_status_message_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_status_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void job_print_begin_status_message(Unit *u, JobType t) {
        const char *format;

        assert(u);

        /* Reload status messages have traditionally not been printed to console. */
        if (!IN_SET(t, JOB_START, JOB_STOP))
                return;

        format = job_get_begin_status_message_format(u, t);

        DISABLE_WARNING_FORMAT_NONLITERAL;
        unit_status_printf(u, "", format);
        REENABLE_WARNING;
}