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
typedef  int /*<<< orphan*/  IFolder ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ CTL_E_FILEALREADYEXISTS ; 
 int /*<<< orphan*/  CreateDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 scalar_t__ IFileSystem3_CreateFolder (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysAllocString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  get_temp_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 

__attribute__((used)) static void test_createfolder(void)
{
    WCHAR buffW[MAX_PATH];
    HRESULT hr;
    BSTR path;
    IFolder *folder;
    BOOL ret;

    get_temp_path(NULL, buffW);
    ret = CreateDirectoryW(buffW, NULL);
    ok(ret, "got %d, %d\n", ret, GetLastError());

    /* create existing directory */
    path = SysAllocString(buffW);
    folder = (void*)0xdeabeef;
    hr = IFileSystem3_CreateFolder(fs3, path, &folder);
    ok(hr == CTL_E_FILEALREADYEXISTS, "got 0x%08x\n", hr);
    ok(folder == NULL, "got %p\n", folder);
    SysFreeString(path);
    RemoveDirectoryW(buffW);
}