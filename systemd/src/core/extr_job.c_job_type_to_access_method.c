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
typedef  scalar_t__ JobType ;

/* Variables and functions */
 scalar_t__ IN_SET (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JOB_RESTART ; 
 int /*<<< orphan*/  JOB_START ; 
 scalar_t__ JOB_STOP ; 
 int /*<<< orphan*/  JOB_TRY_RESTART ; 
 scalar_t__ _JOB_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int) ; 

const char* job_type_to_access_method(JobType t) {
        assert(t >= 0);
        assert(t < _JOB_TYPE_MAX);

        if (IN_SET(t, JOB_START, JOB_RESTART, JOB_TRY_RESTART))
                return "start";
        else if (t == JOB_STOP)
                return "stop";
        else
                return "reload";
}