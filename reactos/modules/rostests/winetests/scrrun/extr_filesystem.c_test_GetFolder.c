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
typedef  int /*<<< orphan*/  IFolder ;
typedef  int /*<<< orphan*/ * HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_Folder ; 
 int /*<<< orphan*/ * CTL_E_PATHNOTFOUND ; 
 int /*<<< orphan*/ * E_INVALIDARG ; 
 int /*<<< orphan*/ * E_POINTER ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 int /*<<< orphan*/ * IFileSystem3_GetFolder (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFolder_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/ * S_OK ; 
 int /*<<< orphan*/ * SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_provideclassinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_GetFolder(void)
{
    static const WCHAR dummyW[] = {'d','u','m','m','y',0};
    WCHAR buffW[MAX_PATH];
    IFolder *folder;
    HRESULT hr;
    BSTR str;

    folder = (void*)0xdeadbeef;
    hr = IFileSystem3_GetFolder(fs3, NULL, &folder);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);
    ok(folder == NULL, "got %p\n", folder);

    hr = IFileSystem3_GetFolder(fs3, NULL, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    /* something that doesn't exist */
    str = SysAllocString(dummyW);

    hr = IFileSystem3_GetFolder(fs3, str, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    folder = (void*)0xdeadbeef;
    hr = IFileSystem3_GetFolder(fs3, str, &folder);
    ok(hr == CTL_E_PATHNOTFOUND, "got 0x%08x\n", hr);
    ok(folder == NULL, "got %p\n", folder);
    SysFreeString(str);

    GetWindowsDirectoryW(buffW, MAX_PATH);
    str = SysAllocString(buffW);
    hr = IFileSystem3_GetFolder(fs3, str, &folder);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    SysFreeString(str);
    test_provideclassinfo(folder, &CLSID_Folder);
    IFolder_Release(folder);
}