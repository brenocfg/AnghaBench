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
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  BG_JOB_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_BackgroundCopyManager ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  ERROR_SERVICE_DISABLED ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IBackgroundCopyManager_CreateJob (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 scalar_t__ S_OK ; 
 scalar_t__ addFileHelper (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_displayName ; 
 int /*<<< orphan*/  test_localName ; 
 int /*<<< orphan*/  test_remoteName ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static HRESULT test_create_manager(void)
{
    HRESULT hres;
    IBackgroundCopyManager *manager = NULL;

    /* Creating BITS instance */
    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL, CLSCTX_LOCAL_SERVER,
                            &IID_IBackgroundCopyManager, (void **) &manager);

    if(hres == HRESULT_FROM_WIN32(ERROR_SERVICE_DISABLED)) {
        win_skip("Needed Service is disabled\n");
        return hres;
    }

    if (hres == S_OK)
    {
        IBackgroundCopyJob *job;
        GUID jobId;

        hres = IBackgroundCopyManager_CreateJob(manager, test_displayName, BG_JOB_TYPE_DOWNLOAD, &jobId, &job);
        if (hres == S_OK)
        {
            hres = addFileHelper(job, test_localName, test_remoteName);
            if (hres != S_OK)
                win_skip("AddFile() with file:// protocol failed. Tests will be skipped.\n");
            IBackgroundCopyJob_Release(job);
        }
        IBackgroundCopyManager_Release(manager);
    }

    return hres;
}