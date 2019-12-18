#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_8__ {int /*<<< orphan*/  anchor_job; } ;
typedef  TYPE_1__ Transaction ;
typedef  int /*<<< orphan*/  Manager ;
typedef  int /*<<< orphan*/  JobMode ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  JOB_IGNORE_DEPENDENCIES ; 
 int /*<<< orphan*/  JOB_ISOLATE ; 
 int /*<<< orphan*/  JOB_NOP ; 
 int /*<<< orphan*/  JOB_REPLACE_IRREVERSIBLY ; 
 int /*<<< orphan*/  _JOB_MODE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  transaction_abort (TYPE_1__*) ; 
 int transaction_activate (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int transaction_add_job_and_dependencies (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transaction_add_propagate_reload_jobs (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transaction_free (TYPE_1__*) ; 
 TYPE_1__* transaction_new (int) ; 

int manager_propagate_reload(Manager *m, Unit *unit, JobMode mode, sd_bus_error *e) {
        int r;
        Transaction *tr;

        assert(m);
        assert(unit);
        assert(mode < _JOB_MODE_MAX);
        assert(mode != JOB_ISOLATE); /* Isolate is only valid for start */

        tr = transaction_new(mode == JOB_REPLACE_IRREVERSIBLY);
        if (!tr)
                return -ENOMEM;

        /* We need an anchor job */
        r = transaction_add_job_and_dependencies(tr, JOB_NOP, unit, NULL, false, false, true, true, e);
        if (r < 0)
                goto tr_abort;

        /* Failure in adding individual dependencies is ignored, so this always succeeds. */
        transaction_add_propagate_reload_jobs(tr, unit, tr->anchor_job, mode == JOB_IGNORE_DEPENDENCIES, e);

        r = transaction_activate(tr, m, mode, NULL, e);
        if (r < 0)
                goto tr_abort;

        transaction_free(tr);
        return 0;

tr_abort:
        transaction_abort(tr);
        transaction_free(tr);
        return r;
}