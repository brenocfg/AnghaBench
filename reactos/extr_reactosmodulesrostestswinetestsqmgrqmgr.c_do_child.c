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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IBackgroundCopyManager ;
typedef  int /*<<< orphan*/  IBackgroundCopyJob ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;

/* Variables and functions */
 int /*<<< orphan*/  BG_JOB_TYPE_DOWNLOAD ; 
 int /*<<< orphan*/  CLSCTX_LOCAL_SERVER ; 
 int /*<<< orphan*/  CLSID_BackgroundCopyManager ; 
 int /*<<< orphan*/  CP_ACP ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBackgroundCopyJob_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IBackgroundCopyManager_CreateJob (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IBackgroundCopyManager_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBackgroundCopyManager ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void do_child(const char *secretA)
{
    WCHAR secretW[MAX_PATH];
    IBackgroundCopyManager *manager = NULL;
    GUID id;
    IBackgroundCopyJob *job;
    HRESULT hres;
    hres = CoCreateInstance(&CLSID_BackgroundCopyManager, NULL,
                            CLSCTX_LOCAL_SERVER, &IID_IBackgroundCopyManager,
                            (void **) &manager);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    MultiByteToWideChar(CP_ACP, 0, secretA, -1, secretW, MAX_PATH);
    hres = IBackgroundCopyManager_CreateJob(manager, secretW,
                                            BG_JOB_TYPE_DOWNLOAD, &id, &job);
    ok(hres == S_OK, "CreateJob in child process\n");
    IBackgroundCopyJob_Release(job);
    IBackgroundCopyManager_Release(manager);
}