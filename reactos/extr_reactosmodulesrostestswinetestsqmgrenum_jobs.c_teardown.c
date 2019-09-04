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

/* Variables and functions */
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumBackgroundCopyJobs_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_enumJobsA ; 
 int /*<<< orphan*/ * test_enumJobsB ; 
 int /*<<< orphan*/ * test_jobA ; 
 int /*<<< orphan*/ * test_jobB ; 
 int /*<<< orphan*/ * test_manager ; 

__attribute__((used)) static void teardown(void)
{
    if (test_enumJobsB)
        IEnumBackgroundCopyJobs_Release(test_enumJobsB);
    test_enumJobsB = NULL;
    if (test_jobB)
        IBackgroundCopyJob_Release(test_jobB);
    test_jobB = NULL;
    if (test_enumJobsA)
        IEnumBackgroundCopyJobs_Release(test_enumJobsA);
    test_enumJobsA = NULL;
    if (test_jobA)
        IBackgroundCopyJob_Release(test_jobA);
    test_jobA = NULL;
    if (test_manager)
        IBackgroundCopyManager_Release(test_manager);
    test_manager = NULL;
}