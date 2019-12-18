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
typedef  float WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BG_JOB_STATE ;

/* Variables and functions */
 scalar_t__ BG_JOB_STATE_ACKNOWLEDGED ; 
 scalar_t__ BG_JOB_STATE_CONNECTING ; 
 scalar_t__ BG_JOB_STATE_QUEUED ; 
 scalar_t__ BG_JOB_STATE_TRANSFERRED ; 
 scalar_t__ BG_JOB_STATE_TRANSFERRING ; 
 int DeleteFileW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 float* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,float*) ; 
 scalar_t__ IBackgroundCopyJob_AddFile (int /*<<< orphan*/ ,float*,int /*<<< orphan*/ ) ; 
 scalar_t__ IBackgroundCopyJob_Complete (int /*<<< orphan*/ ) ; 
 scalar_t__ IBackgroundCopyJob_GetState (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ IBackgroundCopyJob_Resume (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int /*<<< orphan*/  compareFiles (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcatW (float*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcpyW (float*,float const*) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeFile (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_job ; 
 int /*<<< orphan*/  test_localPathA ; 
 int /*<<< orphan*/  test_localPathB ; 
 int /*<<< orphan*/  test_remotePathA ; 
 int /*<<< orphan*/  test_remotePathB ; 

__attribute__((used)) static void test_CompleteLocalURL(void)
{
    static const WCHAR prot[] = {'f','i','l','e',':','/','/', 0};
    static const int timeout_sec = 30;
    WCHAR *urlA, *urlB;
    HRESULT hres;
    BG_JOB_STATE state;
    int i;

    DeleteFileW(test_localPathA);
    DeleteFileW(test_localPathB);
    makeFile(test_remotePathA, "This is a WINE test file for BITS\n");
    makeFile(test_remotePathB, "This is another WINE test file for BITS\n");

    urlA = HeapAlloc(GetProcessHeap(), 0,
                     (7 + lstrlenW(test_remotePathA) + 1) * sizeof urlA[0]);
    urlB = HeapAlloc(GetProcessHeap(), 0,
                     (7 + lstrlenW(test_remotePathB) + 1) * sizeof urlB[0]);
    if (!urlA || !urlB)
    {
        skip("Unable to allocate memory for URLs\n");
        HeapFree(GetProcessHeap(), 0, urlA);
        HeapFree(GetProcessHeap(), 0, urlB);
        return;
    }

    lstrcpyW(urlA, prot);
    lstrcatW(urlA, test_remotePathA);
    lstrcpyW(urlB, prot);
    lstrcatW(urlB, test_remotePathB);

    hres = IBackgroundCopyJob_AddFile(test_job, urlA, test_localPathA);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    hres = IBackgroundCopyJob_AddFile(test_job, urlB, test_localPathB);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    hres = IBackgroundCopyJob_Resume(test_job);
    ok(hres == S_OK, "IBackgroundCopyJob_Resume\n");

    for (i = 0; i < timeout_sec; ++i)
    {
        hres = IBackgroundCopyJob_GetState(test_job, &state);
        ok(hres == S_OK, "IBackgroundCopyJob_GetState\n");
        ok(state == BG_JOB_STATE_QUEUED || state == BG_JOB_STATE_CONNECTING
           || state == BG_JOB_STATE_TRANSFERRING || state == BG_JOB_STATE_TRANSFERRED,
           "Bad state: %d\n", state);
        if (state == BG_JOB_STATE_TRANSFERRED)
            break;
        Sleep(1000);
    }

    ok(i < timeout_sec, "BITS jobs timed out\n");
    hres = IBackgroundCopyJob_Complete(test_job);
    ok(hres == S_OK, "IBackgroundCopyJob_Complete\n");
    hres = IBackgroundCopyJob_GetState(test_job, &state);
    ok(hres == S_OK, "IBackgroundCopyJob_GetState\n");
    ok(state == BG_JOB_STATE_ACKNOWLEDGED, "Bad state: %d\n", state);

    compareFiles(test_remotePathA, test_localPathA);
    compareFiles(test_remotePathB, test_localPathB);

    ok(DeleteFileW(test_remotePathA), "DeleteFile\n");
    ok(DeleteFileW(test_remotePathB), "DeleteFile\n");
    DeleteFileW(test_localPathA);
    DeleteFileW(test_localPathB);

    HeapFree(GetProcessHeap(), 0, urlA);
    HeapFree(GetProcessHeap(), 0, urlB);
}