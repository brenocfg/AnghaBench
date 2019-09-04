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
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumBackgroundCopyJobs_Next (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_enumJobsB ; 
 scalar_t__ test_jobCountB ; 

__attribute__((used)) static void test_Next_walkListNull(void)
{
    HRESULT hres;
    IBackgroundCopyJob *job;
    ULONG i;

    /* Fetch the available jobs */
    for (i = 0; i < test_jobCountB; i++)
    {
        hres = IEnumBackgroundCopyJobs_Next(test_enumJobsB, 1, &job, NULL);
        ok(hres == S_OK, "Next failed: %08x\n", hres);
        IBackgroundCopyJob_Release(job);
    }

    /* Attempt to fetch one more than the number of available jobs */
    hres = IEnumBackgroundCopyJobs_Next(test_enumJobsB, 1, &job, NULL);
    ok(hres == S_FALSE, "Next off end of available jobs failed: %08x\n", hres);
}