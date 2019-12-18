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
typedef  int /*<<< orphan*/  UnitActiveState ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int JobType ;

/* Variables and functions */
 int JOB_NOP ; 
 int JOB_RELOAD ; 
#define  JOB_RELOAD_OR_START 130 
 int JOB_RESTART ; 
 int JOB_START ; 
#define  JOB_TRY_RELOAD 129 
#define  JOB_TRY_RESTART 128 
 int /*<<< orphan*/  UNIT_IS_ACTIVE_OR_RELOADING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_active_state (int /*<<< orphan*/ *) ; 

JobType job_type_collapse(JobType t, Unit *u) {
        UnitActiveState s;

        switch (t) {

        case JOB_TRY_RESTART:
                s = unit_active_state(u);
                if (!UNIT_IS_ACTIVE_OR_RELOADING(s))
                        return JOB_NOP;

                return JOB_RESTART;

        case JOB_TRY_RELOAD:
                s = unit_active_state(u);
                if (!UNIT_IS_ACTIVE_OR_RELOADING(s))
                        return JOB_NOP;

                return JOB_RELOAD;

        case JOB_RELOAD_OR_START:
                s = unit_active_state(u);
                if (!UNIT_IS_ACTIVE_OR_RELOADING(s))
                        return JOB_START;

                return JOB_RELOAD;

        default:
                return t;
        }
}