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
typedef  int UINT ;
typedef  int SFGAOF ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  scalar_t__ LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellItemArray ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  Cleanup () ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFilesFolders () ; 
 int E_UNEXPECTED ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int IShellItemArray_GetAttributes (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  IShellItemArray_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int SFGAO_FOLDER ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SIATTRIBFLAGS_AND ; 
 int /*<<< orphan*/  SIATTRIBFLAGS_OR ; 
 int S_FALSE ; 
 int S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  myPathAddBackslashW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pSHCreateShellItemArrayFromIDLists (int,scalar_t__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pSHCreateShellItemArrayFromShellItem ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_ShellItemArrayGetAttributes(void)
{
    IShellItemArray *psia_files, *psia_folders1, *psia_folders2, *psia_all;
    IShellFolder *pdesktopsf;
    LPCITEMIDLIST pidl_array[5];
    SFGAOF attr;
    HRESULT hr;
    WCHAR curdirW[MAX_PATH];
    WCHAR buf[MAX_PATH];
    UINT i;
    static const WCHAR testdir1W[] = {'t','e','s','t','d','i','r',0};
    static const WCHAR testdir2W[] = {'t','e','s','t','d','i','r','\\','t','e','s','t','d','i','r','2',0};
    static const WCHAR testdir3W[] = {'t','e','s','t','d','i','r','\\','t','e','s','t','d','i','r','3',0};
    static const WCHAR testfile1W[] = {'t','e','s','t','d','i','r','\\','t','e','s','t','1','.','t','x','t',0};
    static const WCHAR testfile2W[] = {'t','e','s','t','d','i','r','\\','t','e','s','t','2','.','t','x','t',0};
    static const WCHAR *testfilesW[5] = { testdir1W, testdir2W, testdir3W, testfile1W, testfile2W };

    if(!pSHCreateShellItemArrayFromShellItem)
    {
        win_skip("No SHCreateShellItemArrayFromShellItem, skipping test...\n");
        return;
    }

    CreateFilesFolders();
    CreateDirectoryA(".\\testdir\\testdir3", NULL);

    SHGetDesktopFolder(&pdesktopsf);

    GetCurrentDirectoryW(MAX_PATH, curdirW);
    myPathAddBackslashW(curdirW);

    for(i = 0; i < 5; i++)
    {
        lstrcpyW(buf, curdirW);
        lstrcatW(buf, testfilesW[i]);
        hr = IShellFolder_ParseDisplayName(pdesktopsf, NULL, NULL, buf, NULL, (LPITEMIDLIST*)&pidl_array[i], NULL);
        ok(hr == S_OK, "got 0x%08x\n", hr);
    }
    IShellFolder_Release(pdesktopsf);

    hr = pSHCreateShellItemArrayFromIDLists(2, pidl_array, &psia_folders1);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = pSHCreateShellItemArrayFromIDLists(2, &pidl_array[1], &psia_folders2);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = pSHCreateShellItemArrayFromIDLists(2, &pidl_array[3], &psia_files);
    ok(hr == S_OK, "got 0x%08x\n", hr);
    hr = pSHCreateShellItemArrayFromIDLists(4, &pidl_array[1], &psia_all); /* All except the first */
    ok(hr == S_OK, "got 0x%08x\n", hr);

    for(i = 0; i < 5; i++)
        ILFree((LPITEMIDLIST)pidl_array[i]);

    /* [testfolder/, testfolder/testfolder2] seems to break in Vista */
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_folders1, SIATTRIBFLAGS_AND, SFGAO_FOLDER, &attr);
    ok(hr == S_OK || broken(hr == E_UNEXPECTED)  /* Vista */, "Got 0x%08x\n", hr);
    ok(attr == SFGAO_FOLDER || broken(attr == 0) /* Vista */, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_folders1, SIATTRIBFLAGS_OR, SFGAO_FOLDER, &attr);
    ok(hr == S_OK || broken(hr == E_UNEXPECTED)  /* Vista */, "Got 0x%08x\n", hr);
    ok(attr == SFGAO_FOLDER || broken(attr == 0) /* Vista */, "Got 0x%08x\n", attr);

    /* [testfolder/testfolder2, testfolder/testfolder3] works */
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_folders2, SIATTRIBFLAGS_AND, SFGAO_FOLDER, &attr);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(attr == SFGAO_FOLDER, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_files, SIATTRIBFLAGS_AND, SFGAO_FOLDER, &attr);
    ok(hr == S_FALSE || broken(hr == S_OK) /* Vista */, "Got 0x%08x\n", hr);
    ok(attr == 0, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_all, SIATTRIBFLAGS_AND, SFGAO_FOLDER, &attr);
    ok(hr == S_FALSE || broken(hr == S_OK) /* Vista */, "Got 0x%08x\n", hr);
    ok(attr == 0, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_folders2, SIATTRIBFLAGS_OR, SFGAO_FOLDER, &attr);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(attr == SFGAO_FOLDER, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_files, SIATTRIBFLAGS_OR, SFGAO_FOLDER, &attr);
    ok(hr == S_FALSE || broken(hr == S_OK) /* Vista */, "Got 0x%08x\n", hr);
    ok(attr == 0, "Got 0x%08x\n", attr);
    attr = 0xdeadbeef;
    hr = IShellItemArray_GetAttributes(psia_all, SIATTRIBFLAGS_OR, SFGAO_FOLDER, &attr);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    ok(attr == SFGAO_FOLDER, "Got 0x%08x\n", attr);

    IShellItemArray_Release(psia_folders1);
    IShellItemArray_Release(psia_folders2);
    IShellItemArray_Release(psia_files);
    IShellItemArray_Release(psia_all);

    RemoveDirectoryA(".\\testdir\\testdir3");
    Cleanup();
}