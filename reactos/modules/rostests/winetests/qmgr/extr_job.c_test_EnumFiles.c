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
typedef  int /*<<< orphan*/  IEnumBackgroundCopyFiles ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ IBackgroundCopyJob_AddFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IBackgroundCopyJob_EnumFiles (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ IEnumBackgroundCopyFiles_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  test_job ; 
 int /*<<< orphan*/  test_localPathA ; 
 int /*<<< orphan*/  test_remotePathA ; 

__attribute__((used)) static void test_EnumFiles(void)
{
    HRESULT hres;
    IEnumBackgroundCopyFiles *enumFiles;
    ULONG res;

    hres = IBackgroundCopyJob_AddFile(test_job, test_remotePathA,
                                      test_localPathA);
    ok(hres == S_OK, "got 0x%08x\n", hres);

    hres = IBackgroundCopyJob_EnumFiles(test_job, &enumFiles);
    ok(hres == S_OK, "EnumFiles failed: 0x%08x\n", hres);

    res = IEnumBackgroundCopyFiles_Release(enumFiles);
    ok(res == 0, "Bad ref count on release: %u\n", res);
}