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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  JobType ;

/* Variables and functions */
 int /*<<< orphan*/  _JOB_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  job_log_begin_status_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  job_print_begin_status_message (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void job_emit_begin_status_message(Unit *u, uint32_t job_id, JobType t) {
        assert(u);
        assert(t >= 0);
        assert(t < _JOB_TYPE_MAX);

        job_log_begin_status_message(u, job_id, t);
        job_print_begin_status_message(u, t);
}