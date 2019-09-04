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
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_displayName ; 
 int /*<<< orphan*/ * test_job ; 
 int /*<<< orphan*/  test_jobId ; 
 int /*<<< orphan*/ * test_manager ; 
 int /*<<< orphan*/  test_type ; 

__attribute__((used)) static BOOL setup(void)
{
    HRESULT hres;

    test_manager = NULL;
    test_job = NULL;
    memset(&test_jobId, 0, sizeof test_jobId);
    test_type = BG_JOB_TYPE_DOWNLOAD;

    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL,
                            CLSCTX_LOCAL_SERVER,
                            &IID_IBackgroundCopyManager,
                            (void **) &test_manager);
    if(hres != S_OK)
        return FALSE;

    hres = IBackgroundCopyManager_CreateJob(test_manager, test_displayName,
                                            test_type, &test_jobId, &test_job);
    if(hres != S_OK)
    {
        IBackgroundCopyManager_Release(test_manager);
        return FALSE;
    }

    return TRUE;
}