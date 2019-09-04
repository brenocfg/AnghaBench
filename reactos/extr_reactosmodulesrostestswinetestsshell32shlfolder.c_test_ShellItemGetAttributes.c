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
typedef  int SFGAOF ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  Cleanup () ; 
 int /*<<< orphan*/  CreateFilesFolders () ; 
 int E_FAIL ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int IShellItem_GetAttributes (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IShellItem_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int SFGAO_FOLDER ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int SHGetSpecialFolderLocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int) ; 
 int S_FALSE ; 
 int S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  myPathAddBackslashW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pSHCreateShellItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_ShellItemGetAttributes(void)
{
    IShellItem *psi, *psi_folder1, *psi_file1;
    IShellFolder *pdesktopsf;
    LPITEMIDLIST pidl_desktop, pidl;
    SFGAOF sfgao;
    HRESULT hr;
    WCHAR curdirW[MAX_PATH];
    WCHAR buf[MAX_PATH];
    static const WCHAR testdir1W[] = {'t','e','s','t','d','i','r',0};
    static const WCHAR testfile1W[] = {'t','e','s','t','d','i','r','\\','t','e','s','t','1','.','t','x','t',0};

    if(!pSHCreateShellItem)
    {
        skip("SHCreateShellItem missing.\n");
        return;
    }

    hr = SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl_desktop);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr))
    {
        hr = pSHCreateShellItem(NULL, NULL, pidl_desktop, &psi);
        ok(hr == S_OK, "Got 0x%08x\n", hr);
        ILFree(pidl_desktop);
    }
    if(FAILED(hr))
    {
        skip("Skipping tests.\n");
        return;
    }

    if(0)
    {
        /* Crashes on native (Win 7) */
        IShellItem_GetAttributes(psi, 0, NULL);
    }

    /* Test GetAttributes on the desktop folder. */
    sfgao = 0xdeadbeef;
    hr = IShellItem_GetAttributes(psi, SFGAO_FOLDER, &sfgao);
    ok(hr == S_OK || broken(hr == E_FAIL) /* <Vista */, "Got 0x%08x\n", hr);
    ok(sfgao == SFGAO_FOLDER || broken(sfgao == 0) /* <Vista */, "Got 0x%08x\n", sfgao);

    IShellItem_Release(psi);

    CreateFilesFolders();

    SHGetDesktopFolder(&pdesktopsf);

    GetCurrentDirectoryW(MAX_PATH, curdirW);
    myPathAddBackslashW(curdirW);

    lstrcpyW(buf, curdirW);
    lstrcatW(buf, testdir1W);
    hr = IShellFolder_ParseDisplayName(pdesktopsf, NULL, NULL, buf, NULL, &pidl, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = pSHCreateShellItem(NULL, NULL, pidl, &psi_folder1);
    ok(hr == S_OK, "Got 0x%08x\n", sfgao);
    ILFree(pidl);

    lstrcpyW(buf, curdirW);
    lstrcatW(buf, testfile1W);
    hr = IShellFolder_ParseDisplayName(pdesktopsf, NULL, NULL, buf, NULL, &pidl, NULL);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = pSHCreateShellItem(NULL, NULL, pidl, &psi_file1);
    ok(hr == S_OK, "Got 0x%08x\n", sfgao);
    ILFree(pidl);

    IShellFolder_Release(pdesktopsf);

    sfgao = 0xdeadbeef;
    hr = IShellItem_GetAttributes(psi_folder1, 0, &sfgao);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(sfgao == 0, "Got 0x%08x\n", sfgao);

    sfgao = 0xdeadbeef;
    hr = IShellItem_GetAttributes(psi_folder1, SFGAO_FOLDER, &sfgao);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(sfgao == SFGAO_FOLDER, "Got 0x%08x\n", sfgao);

    sfgao = 0xdeadbeef;
    hr = IShellItem_GetAttributes(psi_file1, SFGAO_FOLDER, &sfgao);
    ok(hr == S_FALSE, "Got 0x%08x\n", hr);
    ok(sfgao == 0, "Got 0x%08x\n", sfgao);

    IShellItem_Release(psi_folder1);
    IShellItem_Release(psi_file1);

    Cleanup();
}