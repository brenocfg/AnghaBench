#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_20__ {scalar_t__ cb; } ;
struct TYPE_25__ {TYPE_1__ mkid; } ;
struct TYPE_22__ {int cb; int /*<<< orphan*/ * abID; } ;
struct TYPE_24__ {TYPE_3__ mkid; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_23__ {TYPE_2__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  STRRET ;
typedef  TYPE_4__ SHITEMID ;
typedef  int /*<<< orphan*/  LPSHELLFOLDER ;
typedef  TYPE_5__* LPITEMIDLIST ;
typedef  TYPE_5__* LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_7__ ITEMIDLIST ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BYTE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CSIDL_PERSONAL ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_CANCELLED ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetFileAttributesA (char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 TYPE_5__* ILFindLastID (TYPE_5__*) ; 
 int /*<<< orphan*/  ILFree (TYPE_5__*) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IShellFolder_BindToObject (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IShellFolder_GetDisplayNameOf (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_ParseDisplayName (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_5__**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellFolder_SetNameOf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,char const*,int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SHBindToParent (TYPE_5__*,int /*<<< orphan*/ *,void**,TYPE_5__**) ; 
 int /*<<< orphan*/  SHGDN_FORPARSING ; 
 int /*<<< orphan*/  SHGDN_NORMAL ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetPathFromIDListW (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  StrRetToBufW (int /*<<< orphan*/ *,TYPE_5__*,char*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetDisplayName(void)
{
    BOOL result;
    HRESULT hr;
    HANDLE hTestFile;
    WCHAR wszTestFile[MAX_PATH], wszTestFile2[MAX_PATH];
    char szTestFile[MAX_PATH], szTestDir[MAX_PATH];
    DWORD attr;
    STRRET strret;
    LPSHELLFOLDER psfDesktop, psfPersonal;
    IUnknown *psfFile;
    SHITEMID emptyitem = { 0, { 0 } };
    LPITEMIDLIST pidlTestFile, pidlEmpty = (LPITEMIDLIST)&emptyitem;
    LPCITEMIDLIST pidlLast;
    static const CHAR szFileName[] = "winetest.foo";
    static const WCHAR wszFileName[] = { 'w','i','n','e','t','e','s','t','.','f','o','o',0 };
    static const WCHAR wszDirName[] = { 'w','i','n','e','t','e','s','t',0 };

    /* It's ok to use this fixed path. Call will fail anyway. */
    WCHAR wszAbsoluteFilename[] = { 'C',':','\\','w','i','n','e','t','e','s','t', 0 };
    LPITEMIDLIST pidlNew;

    /* I'm trying to figure if there is a functional difference between calling
     * SHGetPathFromIDListW and calling GetDisplayNameOf(SHGDN_FORPARSING) after
     * binding to the shellfolder. One thing I thought of was that perhaps 
     * SHGetPathFromIDListW would be able to get the path to a file, which does
     * not exist anymore, while the other method wouldn't. It turns out there's
     * no functional difference in this respect.
     */

    /* First creating a directory in MyDocuments and a file in this directory. */
    result = SHGetSpecialFolderPathA(NULL, szTestDir, CSIDL_PERSONAL, FALSE);
    ok(result, "SHGetSpecialFolderPathA failed! Last error: %u\n", GetLastError());
    if (!result) return;

    /* Use ANSI file functions so this works on Windows 9x */
    lstrcatA(szTestDir, "\\winetest");
    CreateDirectoryA(szTestDir, NULL);
    attr=GetFileAttributesA(szTestDir);
    if (attr == INVALID_FILE_ATTRIBUTES || !(attr & FILE_ATTRIBUTE_DIRECTORY))
    {
        ok(0, "unable to create the '%s' directory\n", szTestDir);
        return;
    }

    lstrcpyA(szTestFile, szTestDir);
    lstrcatA(szTestFile, "\\");
    lstrcatA(szTestFile, szFileName);
    hTestFile = CreateFileA(szTestFile, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    ok((hTestFile != INVALID_HANDLE_VALUE), "CreateFileA failed! Last error: %u\n", GetLastError());
    if (hTestFile == INVALID_HANDLE_VALUE) return;
    CloseHandle(hTestFile);

    /* Getting an itemidlist for the file. */
    hr = SHGetDesktopFolder(&psfDesktop);
    ok(hr == S_OK, "SHGetDesktopFolder failed! hr = %08x\n", hr);
    if (hr != S_OK) return;

    MultiByteToWideChar(CP_ACP, 0, szTestFile, -1, wszTestFile, MAX_PATH);

    hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, wszTestFile, NULL, &pidlTestFile, NULL);
    ok(hr == S_OK, "Desktop->ParseDisplayName failed! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfDesktop);
        return;
    }

    pidlLast = ILFindLastID(pidlTestFile);
    ok(pidlLast->mkid.cb >= 76, "Expected pidl length of at least 76, got %d.\n", pidlLast->mkid.cb);
    if (pidlLast->mkid.cb >= 28) {
        ok(!lstrcmpA((CHAR*)&pidlLast->mkid.abID[12], szFileName),
            "Filename should be stored as ansi-string at this position!\n");
    }
    /* WinXP and up store the filenames as both ANSI and UNICODE in the pidls */
    if (pidlLast->mkid.cb >= 76) {
        ok(!lstrcmpW((WCHAR*)&pidlLast->mkid.abID[46], wszFileName) ||
            (pidlLast->mkid.cb >= 94 && !lstrcmpW((WCHAR*)&pidlLast->mkid.abID[64], wszFileName)) ||  /* Vista */
            (pidlLast->mkid.cb >= 98 && !lstrcmpW((WCHAR*)&pidlLast->mkid.abID[68], wszFileName)) ||  /* Win7 */
            (pidlLast->mkid.cb >= 102 && !lstrcmpW((WCHAR*)&pidlLast->mkid.abID[72], wszFileName)),   /* Win8 */
            "Filename should be stored as wchar-string at this position!\n");
    }
    
    /* It seems as if we cannot bind to regular files on windows, but only directories. 
     */
    hr = IShellFolder_BindToObject(psfDesktop, pidlTestFile, NULL, &IID_IUnknown, (VOID**)&psfFile);
    ok (hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
        hr == E_NOTIMPL, /* Vista */
        "hr = %08x\n", hr);
    if (hr == S_OK) {
        IUnknown_Release(psfFile);
    }

    /* Some tests for IShellFolder::SetNameOf */
    hr = SHBindToParent(pidlTestFile, &IID_IShellFolder, (void **)&psfPersonal, &pidlLast);
    ok(hr == S_OK, "SHBindToParent failed! hr = %08x\n", hr);

    /* The pidl returned through the last parameter of SetNameOf is a simple one. */
    hr = IShellFolder_SetNameOf(psfPersonal, NULL, pidlLast, wszDirName, SHGDN_NORMAL, &pidlNew);
    ok (hr == S_OK, "SetNameOf failed! hr = %08x\n", hr);

    ok (((ITEMIDLIST *)((BYTE *)pidlNew + pidlNew->mkid.cb))->mkid.cb == 0,
        "pidl returned from SetNameOf should be simple!\n");

    /* Passing an absolute path to SetNameOf fails. The HRESULT code indicates that SetNameOf
     * is implemented on top of SHFileOperation in WinXP. */
    hr = IShellFolder_SetNameOf(psfPersonal, NULL, pidlNew, wszAbsoluteFilename, SHGDN_FORPARSING, NULL);
    ok (hr == HRESULT_FROM_WIN32(ERROR_CANCELLED), "SetNameOf succeeded! hr = %08x\n", hr);

    /* Rename the file back to its original name. SetNameOf ignores the fact, that the
     * SHGDN flags specify an absolute path. */
    hr = IShellFolder_SetNameOf(psfPersonal, NULL, pidlNew, wszFileName, SHGDN_FORPARSING, NULL);
    ok (hr == S_OK, "SetNameOf failed! hr = %08x\n", hr);

    ILFree(pidlNew);
    IShellFolder_Release(psfPersonal);

    /* Deleting the file and the directory */
    DeleteFileA(szTestFile);
    RemoveDirectoryA(szTestDir);

    /* SHGetPathFromIDListW still works, although the file is not present anymore. */
    result = SHGetPathFromIDListW(pidlTestFile, wszTestFile2);
    ok (result, "SHGetPathFromIDListW failed! Last error: %u\n", GetLastError());
    ok (!lstrcmpiW(wszTestFile, wszTestFile2), "SHGetPathFromIDListW returns incorrect path!\n");

    /* SHBindToParent fails, if called with a NULL PIDL. */
    hr = SHBindToParent(NULL, &IID_IShellFolder, (void **)&psfPersonal, &pidlLast);
    ok (hr == E_INVALIDARG || broken(hr == E_OUTOFMEMORY) /* XP */,
        "SHBindToParent(NULL) should fail! hr = %08x\n", hr);

    /* But it succeeds with an empty PIDL. */
    hr = SHBindToParent(pidlEmpty, &IID_IShellFolder, (void **)&psfPersonal, &pidlLast);
    ok (hr == S_OK, "SHBindToParent(empty PIDL) should succeed! hr = %08x\n", hr);
    ok (pidlLast == pidlEmpty, "The last element of an empty PIDL should be the PIDL itself!\n");
    if (hr == S_OK)
        IShellFolder_Release(psfPersonal);

    /* Binding to the folder and querying the display name of the file also works. */
    hr = SHBindToParent(pidlTestFile, &IID_IShellFolder, (void **)&psfPersonal, &pidlLast);
    ok (hr == S_OK, "SHBindToParent failed! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfDesktop);
        return;
    }

    /* This test shows that Windows doesn't allocate a new pidlLast, but returns a pointer into
     * pidlTestFile (In accordance with MSDN). */
    ok (ILFindLastID(pidlTestFile) == pidlLast,
                                "SHBindToParent doesn't return the last id of the pidl param!\n");

    hr = IShellFolder_GetDisplayNameOf(psfPersonal, pidlLast, SHGDN_FORPARSING, &strret);
    ok (hr == S_OK, "Personal->GetDisplayNameOf failed! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfDesktop);
        IShellFolder_Release(psfPersonal);
        return;
    }

    hr = StrRetToBufW(&strret, pidlLast, wszTestFile2, MAX_PATH);
    ok (hr == S_OK, "StrRetToBufW failed! hr = %08x\n", hr);
    ok (!lstrcmpiW(wszTestFile, wszTestFile2), "GetDisplayNameOf returns incorrect path!\n");

    ILFree(pidlTestFile);
    IShellFolder_Release(psfDesktop);
    IShellFolder_Release(psfPersonal);
}