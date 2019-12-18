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
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BG_JOB_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_BackgroundCopyManager ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IBackgroundCopyManager_CreateJob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ IBackgroundCopyManager_EnumJobs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumBackgroundCopyJobs_GetCount (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_displayNameA ; 
 int /*<<< orphan*/  test_displayNameB ; 
 int /*<<< orphan*/  test_enumJobsA ; 
 int /*<<< orphan*/  test_enumJobsB ; 
 int /*<<< orphan*/ * test_jobA ; 
 int /*<<< orphan*/ * test_jobB ; 
 int /*<<< orphan*/  test_jobCountB ; 
 int /*<<< orphan*/  test_jobIdA ; 
 int /*<<< orphan*/  test_jobIdB ; 
 int /*<<< orphan*/ * test_manager ; 

__attribute__((used)) static BOOL setup(void)
{
    HRESULT hres;

    test_manager = NULL;
    test_jobA = NULL;
    test_jobB = NULL;
    memset(&test_jobIdA, 0, sizeof test_jobIdA);
    memset(&test_jobIdB, 0, sizeof test_jobIdB);

    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL,
                            CLSCTX_LOCAL_SERVER, &IID_IBackgroundCopyManager,
                            (void **) &test_manager);
    if(hres != S_OK)
        return FALSE;

    hres = IBackgroundCopyManager_CreateJob(test_manager, test_displayNameA,
                                            BG_JOB_TYPE_DOWNLOAD, &test_jobIdA,
                                            &test_jobA);
    if(hres != S_OK)
        return FALSE;

    hres = IBackgroundCopyManager_EnumJobs(test_manager, 0, &test_enumJobsA);
    if(hres != S_OK)
        return FALSE;

    hres = IBackgroundCopyManager_CreateJob(test_manager, test_displayNameB,
                                            BG_JOB_TYPE_DOWNLOAD, &test_jobIdB,
                                            &test_jobB);
    if(hres != S_OK)
        return FALSE;

    hres = IBackgroundCopyManager_EnumJobs(test_manager, 0, &test_enumJobsB);
    if(hres != S_OK)
        return FALSE;

    hres = IEnumBackgroundCopyJobs_GetCount(test_enumJobsB, &test_jobCountB);
    if (hres != S_OK)
        return FALSE;

    return TRUE;
}