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
typedef  int /*<<< orphan*/  Name ;
typedef  int JobType ;

/* Variables and functions */
 int JOB_TYPE_UNKNOWN ; 
 int _MAX_JOB_TYPE ; 
 int /*<<< orphan*/ * job_type_names ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static JobType
get_job_type_from_name(Name job_type_name)
{
	int i;

	for (i = 0; i < _MAX_JOB_TYPE; i++)
		if (namestrcmp(job_type_name, job_type_names[i]) == 0)
			return i;
	return JOB_TYPE_UNKNOWN;
}