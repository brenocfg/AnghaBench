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
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  char* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  GetSystemDirectoryW (char*,int /*<<< orphan*/ ) ; 
 int GetTempPathW (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ IFileSystem3_GetSpecialFolder (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IFolder_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFolder_get_Path (int /*<<< orphan*/ *,char**) ; 
 int MAX_PATH ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (char*) ; 
 scalar_t__ SystemFolder ; 
 scalar_t__ TemporaryFolder ; 
 scalar_t__ WindowsFolder ; 
 int /*<<< orphan*/  fs3 ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_GetSpecialFolder(void)
{
    WCHAR pathW[MAX_PATH];
    IFolder *folder;
    HRESULT hr;
    DWORD ret;
    BSTR path;

    hr = IFileSystem3_GetSpecialFolder(fs3, WindowsFolder, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    hr = IFileSystem3_GetSpecialFolder(fs3, TemporaryFolder+1, NULL);
    ok(hr == E_POINTER, "got 0x%08x\n", hr);

    hr = IFileSystem3_GetSpecialFolder(fs3, TemporaryFolder+1, &folder);
    ok(hr == E_INVALIDARG, "got 0x%08x\n", hr);

    hr = IFileSystem3_GetSpecialFolder(fs3, WindowsFolder, &folder);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IFolder_get_Path(folder, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    GetWindowsDirectoryW(pathW, ARRAY_SIZE(pathW));
    ok(!lstrcmpiW(pathW, path), "got %s, expected %s\n", wine_dbgstr_w(path), wine_dbgstr_w(pathW));
    SysFreeString(path);
    IFolder_Release(folder);

    hr = IFileSystem3_GetSpecialFolder(fs3, SystemFolder, &folder);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IFolder_get_Path(folder, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    GetSystemDirectoryW(pathW, ARRAY_SIZE(pathW));
    ok(!lstrcmpiW(pathW, path), "got %s, expected %s\n", wine_dbgstr_w(path), wine_dbgstr_w(pathW));
    SysFreeString(path);
    IFolder_Release(folder);

    hr = IFileSystem3_GetSpecialFolder(fs3, TemporaryFolder, &folder);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = IFolder_get_Path(folder, &path);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    ret = GetTempPathW(ARRAY_SIZE(pathW), pathW);
    if (ret && pathW[ret-1] == '\\')
        pathW[ret-1] = 0;

    ok(!lstrcmpiW(pathW, path), "got %s, expected %s\n", wine_dbgstr_w(path), wine_dbgstr_w(pathW));
    SysFreeString(path);
    IFolder_Release(folder);
}