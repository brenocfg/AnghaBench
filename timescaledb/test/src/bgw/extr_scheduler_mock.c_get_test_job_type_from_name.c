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
typedef  int TestJobType ;
typedef  int /*<<< orphan*/  Name ;

/* Variables and functions */
 int _MAX_TEST_JOB_TYPE ; 
 scalar_t__ namestrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * test_job_type_names ; 

__attribute__((used)) static TestJobType
get_test_job_type_from_name(Name job_type_name)
{
	int i;

	for (i = 0; i < _MAX_TEST_JOB_TYPE; i++)
	{
		if (namestrcmp(job_type_name, test_job_type_names[i]) == 0)
			return i;
	}
	return _MAX_TEST_JOB_TYPE;
}