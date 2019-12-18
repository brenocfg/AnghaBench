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
typedef  scalar_t__ WCHAR ;
typedef  scalar_t__ UINT ;
typedef  scalar_t__ LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GetCurrentProcess () ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetSystemDirectoryW (scalar_t__*,int) ; 
 scalar_t__ GetSystemWow64DirectoryW (scalar_t__*,int) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (scalar_t__*,int) ; 
 int /*<<< orphan*/  ILFree (scalar_t__) ; 
 scalar_t__ ILIsEqual (scalar_t__,scalar_t__) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SHParseDisplayName (scalar_t__*,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 scalar_t__* get_empty_cddrive () ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pIsWow64Process (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_SHParseDisplayName(void)
{
    LPITEMIDLIST pidl1, pidl2;
    IShellFolder *desktop;
    WCHAR dirW[MAX_PATH];
    WCHAR nameW[10];
    WCHAR *cdrom;
    HRESULT hr;
    BOOL ret, is_wow64;

if (0)
{
    /* crashes on native */
    SHParseDisplayName(NULL, NULL, NULL, 0, NULL);
    nameW[0] = 0;
    SHParseDisplayName(nameW, NULL, NULL, 0, NULL);
}

    pidl1 = (LPITEMIDLIST)0xdeadbeef;
    hr = SHParseDisplayName(NULL, NULL, &pidl1, 0, NULL);
    ok(broken(hr == E_OUTOFMEMORY) /* < Vista */ ||
       hr == E_INVALIDARG, "failed %08x\n", hr);
    ok(pidl1 == 0, "expected null ptr, got %p\n", pidl1);

    /* dummy name */
    nameW[0] = 0;
    hr = SHParseDisplayName(nameW, NULL, &pidl1, 0, NULL);
    ok(hr == S_OK, "failed %08x\n", hr);
    hr = SHGetDesktopFolder(&desktop);
    ok(hr == S_OK, "failed %08x\n", hr);
    hr = IShellFolder_ParseDisplayName(desktop, NULL, NULL, nameW, NULL, &pidl2, NULL);
    ok(hr == S_OK, "failed %08x\n", hr);
    ret = ILIsEqual(pidl1, pidl2);
    ok(ret == TRUE, "expected equal idls\n");
    ILFree(pidl1);
    ILFree(pidl2);

    /* with path */
    GetWindowsDirectoryW( dirW, MAX_PATH );

    hr = SHParseDisplayName(dirW, NULL, &pidl1, 0, NULL);
    ok(hr == S_OK, "failed %08x\n", hr);
    hr = IShellFolder_ParseDisplayName(desktop, NULL, NULL, dirW, NULL, &pidl2, NULL);
    ok(hr == S_OK, "failed %08x\n", hr);

    ret = ILIsEqual(pidl1, pidl2);
    ok(ret == TRUE, "expected equal idls\n");
    ILFree(pidl1);
    ILFree(pidl2);

    /* system32 is not redirected to syswow64 on WOW64 */
    if (!pIsWow64Process || !pIsWow64Process( GetCurrentProcess(), &is_wow64 )) is_wow64 = FALSE;
    if (is_wow64)
    {
        UINT len;
        *dirW = 0;
        len = GetSystemDirectoryW(dirW, MAX_PATH);
        ok(len > 0, "GetSystemDirectoryW failed: %u\n", GetLastError());
        hr = SHParseDisplayName(dirW, NULL, &pidl1, 0, NULL);
        ok(hr == S_OK, "failed %08x\n", hr);
        *dirW = 0;
        len = GetSystemWow64DirectoryW(dirW, MAX_PATH);
        ok(len > 0, "GetSystemWow64DirectoryW failed: %u\n", GetLastError());
        hr = SHParseDisplayName(dirW, NULL, &pidl2, 0, NULL);
        ok(hr == S_OK, "failed %08x\n", hr);
        ret = ILIsEqual(pidl1, pidl2);
        ok(ret == FALSE, "expected different idls\n");
        ILFree(pidl1);
        ILFree(pidl2);
    }

    IShellFolder_Release(desktop);

    cdrom = get_empty_cddrive();
    if (!cdrom)
        skip("No empty cdrom drive found, skipping test\n");
    else
    {
        hr = SHParseDisplayName(cdrom, NULL, &pidl1, 0, NULL);
        ok(hr == S_OK, "failed %08x\n", hr);
        if (SUCCEEDED(hr)) ILFree(pidl1);
    }
}