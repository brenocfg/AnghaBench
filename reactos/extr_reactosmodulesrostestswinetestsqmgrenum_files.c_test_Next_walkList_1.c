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
typedef  int /*<<< orphan*/  IBackgroundCopyFile ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IBackgroundCopyFile_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumBackgroundCopyFiles_Next (int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,scalar_t__*) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_enumFiles ; 
 scalar_t__ test_fileCount ; 

__attribute__((used)) static void test_Next_walkList_1(void)
{
    HRESULT hres;
    IBackgroundCopyFile *file;
    ULONG fetched;
    ULONG i;

    /* Fetch the available files */
    for (i = 0; i < test_fileCount; i++)
    {
        file = NULL;
        fetched = 0;
        hres = IEnumBackgroundCopyFiles_Next(test_enumFiles, 1, &file, &fetched);
        ok(hres == S_OK, "Next failed: %08x\n", hres);
        ok(fetched == 1, "Next returned the incorrect number of files: %08x\n", hres);
        ok(file != NULL, "Next returned NULL\n");
        if (file)
            IBackgroundCopyFile_Release(file);
    }

    /* Attempt to fetch one more than the number of available files */
    fetched = 0;
    hres = IEnumBackgroundCopyFiles_Next(test_enumFiles, 1, &file, &fetched);
    ok(hres == S_FALSE, "Next off end of available files failed: %08x\n", hres);
    ok(fetched == 0, "Next returned the incorrect number of files: %08x\n", hres);
}