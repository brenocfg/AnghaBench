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
typedef  char WCHAR ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/  IEnumBackgroundCopyJobs ;
typedef  int /*<<< orphan*/  IBackgroundCopyManager ;
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_BackgroundCopyManager ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoTaskMemFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetTickCount () ; 
 int /*<<< orphan*/  IBackgroundCopyJob_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IBackgroundCopyManager_EnumJobs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumBackgroundCopyJobs_GetCount (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IEnumBackgroundCopyJobs_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumBackgroundCopyJobs_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 int MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ lstrcmpW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  run_child (char*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  wsprintfW (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_globalness(void)
{
    static const WCHAR format[] = {'t','e','s','t','_','%','u', 0};
    WCHAR secretName[MAX_PATH];
    IEnumBackgroundCopyJobs* enumJobs;
    IBackgroundCopyManager *manager = NULL;
    HRESULT hres;
    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL,
                            CLSCTX_LOCAL_SERVER, &IID_IBackgroundCopyManager,
                            (void **) &manager);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    wsprintfW(secretName, format, GetTickCount());
    run_child(secretName);

    hres = IBackgroundCopyManager_EnumJobs(manager, 0, &enumJobs);
    ok(hres == S_OK, "EnumJobs failed: %08x\n", hres);
    if(hres != S_OK)
        skip("Unable to create job enumerator.\n");
    else
    {
        ULONG i, n;
        IBackgroundCopyJob *job;
        BOOL found = FALSE;

        hres = IEnumBackgroundCopyJobs_GetCount(enumJobs, &n);
        ok(hres == S_OK, "GetCount failed: %08x\n", hres);
        for (i = 0; i < n && !found; ++i)
        {
            LPWSTR name;
            IEnumBackgroundCopyJobs_Next(enumJobs, 1, &job, NULL);
            IBackgroundCopyJob_GetDisplayName(job, &name);
            if (lstrcmpW(name, secretName) == 0)
                found = TRUE;
            CoTaskMemFree(name);
            IBackgroundCopyJob_Release(job);
        }

        IEnumBackgroundCopyJobs_Release(enumJobs);
        ok(found, "Adding a job in another process failed\n");
    }

    IBackgroundCopyManager_Release(manager);
}