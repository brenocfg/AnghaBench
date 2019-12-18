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
typedef  scalar_t__ JobType ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ job_type_collapse (scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ job_type_lookup_merge (scalar_t__,scalar_t__) ; 

int job_type_merge_and_collapse(JobType *a, JobType b, Unit *u) {
        JobType t;

        t = job_type_lookup_merge(*a, b);
        if (t < 0)
                return -EEXIST;

        *a = job_type_collapse(t, u);
        return 0;
}