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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ ** HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumBackgroundCopyJobs_Next (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_enumJobsB ; 
 int test_jobCountB ; 

__attribute__((used)) static void test_Next_walkList_2(void)
{
    HRESULT hres;
    IBackgroundCopyJob **jobs;
    ULONG fetched;
    ULONG i;

    jobs = HeapAlloc(GetProcessHeap(), 0, test_jobCountB * sizeof *jobs);
    for (i = 0; i < test_jobCountB; i++)
        jobs[i] = NULL;

    fetched = 0;
    hres = IEnumBackgroundCopyJobs_Next(test_enumJobsB, test_jobCountB, jobs, &fetched);
    ok(hres == S_OK, "Next failed: %08x\n", hres);
    ok(fetched == test_jobCountB, "Next returned the incorrect number of jobs: %08x\n", hres);

    for (i = 0; i < test_jobCountB; i++)
    {
        ok(jobs[i] != NULL, "Next returned NULL\n");
        if (jobs[i])
            IBackgroundCopyJob_Release(jobs[i]);
    }

    HeapFree(GetProcessHeap(), 0, jobs);
}