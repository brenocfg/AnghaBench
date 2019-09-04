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
typedef  int /*<<< orphan*/  IBackgroundCopyManager ;
typedef  int /*<<< orphan*/  IBackgroundCopyJobHttpOptions ;
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_BackgroundCopyManager ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IBackgroundCopyJobHttpOptions_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Cancel (int /*<<< orphan*/ *) ; 
 scalar_t__ IBackgroundCopyJob_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IBackgroundCopyManager_CreateJob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyJobHttpOptions ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  test_displayName ; 
 int /*<<< orphan*/  test_jobId ; 
 int /*<<< orphan*/  test_type ; 

__attribute__((used)) static BOOL check_bits25(void)
{
    HRESULT hres;
    IBackgroundCopyManager *manager;
    IBackgroundCopyJob *job;
    IBackgroundCopyJobHttpOptions *options;

    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL,
                            CLSCTX_LOCAL_SERVER, &IID_IBackgroundCopyManager,
                            (void **)&manager);
    if (hres != S_OK) return FALSE;

    hres = IBackgroundCopyManager_CreateJob(manager, test_displayName, test_type, &test_jobId, &job);
    if (hres != S_OK)
    {
        IBackgroundCopyManager_Release(manager);
        return FALSE;
    }

    hres = IBackgroundCopyJob_QueryInterface(job, &IID_IBackgroundCopyJobHttpOptions, (void **)&options);
    IBackgroundCopyJob_Cancel(job);
    IBackgroundCopyJob_Release(job);
    if (hres != S_OK)
    {
        IBackgroundCopyManager_Release(manager);
        return FALSE;
    }

    IBackgroundCopyJobHttpOptions_Release(options);
    IBackgroundCopyManager_Release(manager);
    return TRUE;
}