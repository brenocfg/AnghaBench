#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
typedef  int UINT ;
struct TYPE_3__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {TYPE_1__ member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ SHITEMID ;
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IPersist ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ HANDLE ;
typedef  int /*<<< orphan*/  CLSID ;
typedef  char CHAR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSID_ShellDocObjView ; 
 int /*<<< orphan*/  CP_ACP ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetCurrentDirectoryA (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int GetSystemDirectoryA (char*,int) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IPersist ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMalloc_Free (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IPersist_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersist_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SHGetSpecialFolderPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcatA (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  ppM ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  trace (char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 scalar_t__ wine_dbgstr_guid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_BindToObject(void)
{
    HRESULT hr;
    UINT cChars;
    IShellFolder *psfDesktop, *psfChild, *psfMyComputer, *psfSystemDir;
    SHITEMID emptyitem = { 0, { 0 } };
    LPITEMIDLIST pidlMyComputer, pidlSystemDir, pidl, pidlEmpty = (LPITEMIDLIST)&emptyitem;
    WCHAR wszSystemDir[MAX_PATH];
    char szSystemDir[MAX_PATH];
    char buf[MAX_PATH];
    WCHAR path[MAX_PATH];
    CHAR pathA[MAX_PATH];
    HANDLE hfile;
    WCHAR wszMyComputer[] = { 
        ':',':','{','2','0','D','0','4','F','E','0','-','3','A','E','A','-','1','0','6','9','-',
        'A','2','D','8','-','0','8','0','0','2','B','3','0','3','0','9','D','}',0 };
    static const CHAR filename_html[] = "winetest.html";
    static const CHAR filename_txt[] = "winetest.txt";
    static const CHAR filename_foo[] = "winetest.foo";

    /* The following tests shows that BindToObject should fail with E_INVALIDARG if called
     * with an empty pidl. This is tested for Desktop, MyComputer and the FS ShellFolder
     */
    hr = SHGetDesktopFolder(&psfDesktop);
    ok (hr == S_OK, "SHGetDesktopFolder failed! hr = %08x\n", hr);
    if (hr != S_OK) return;
    
    hr = IShellFolder_BindToObject(psfDesktop, pidlEmpty, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG, "Desktop's BindToObject should fail, when called with empty pidl! hr = %08x\n", hr);

    hr = IShellFolder_BindToObject(psfDesktop, NULL, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG, "Desktop's BindToObject should fail, when called with NULL pidl! hr = %08x\n", hr);

    hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, wszMyComputer, NULL, &pidlMyComputer, NULL);
    ok (hr == S_OK, "Desktop's ParseDisplayName failed to parse MyComputer's CLSID! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfDesktop);
        return;
    }
    
    hr = IShellFolder_BindToObject(psfDesktop, pidlMyComputer, NULL, &IID_IShellFolder, (LPVOID*)&psfMyComputer);
    ok (hr == S_OK, "Desktop failed to bind to MyComputer object! hr = %08x\n", hr);
    IShellFolder_Release(psfDesktop);
    IMalloc_Free(ppM, pidlMyComputer);
    if (hr != S_OK) return;

    hr = IShellFolder_BindToObject(psfMyComputer, pidlEmpty, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG, "MyComputers's BindToObject should fail, when called with empty pidl! hr = %08x\n", hr);

    hr = IShellFolder_BindToObject(psfMyComputer, NULL, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG, "MyComputers's BindToObject should fail, when called with NULL pidl! hr = %08x\n", hr);

    cChars = GetSystemDirectoryA(szSystemDir, MAX_PATH);
    ok (cChars > 0 && cChars < MAX_PATH, "GetSystemDirectoryA failed! LastError: %u\n", GetLastError());
    if (cChars == 0 || cChars >= MAX_PATH) {
        IShellFolder_Release(psfMyComputer);
        return;
    }
    MultiByteToWideChar(CP_ACP, 0, szSystemDir, -1, wszSystemDir, MAX_PATH);
    
    hr = IShellFolder_ParseDisplayName(psfMyComputer, NULL, NULL, wszSystemDir, NULL, &pidlSystemDir, NULL);
    ok (hr == S_OK, "MyComputers's ParseDisplayName failed to parse the SystemDirectory! hr = %08x\n", hr);
    if (hr != S_OK) {
        IShellFolder_Release(psfMyComputer);
        return;
    }

    hr = IShellFolder_BindToObject(psfMyComputer, pidlSystemDir, NULL, &IID_IShellFolder, (LPVOID*)&psfSystemDir);
    ok (hr == S_OK, "MyComputer failed to bind to a FileSystem ShellFolder! hr = %08x\n", hr);
    IShellFolder_Release(psfMyComputer);
    IMalloc_Free(ppM, pidlSystemDir);
    if (hr != S_OK) return;

    hr = IShellFolder_BindToObject(psfSystemDir, pidlEmpty, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG, 
        "FileSystem ShellFolder's BindToObject should fail, when called with empty pidl! hr = %08x\n", hr);

    hr = IShellFolder_BindToObject(psfSystemDir, NULL, NULL, &IID_IShellFolder, (LPVOID*)&psfChild);
    ok (hr == E_INVALIDARG,
        "FileSystem ShellFolder's BindToObject should fail, when called with NULL pidl! hr = %08x\n", hr);

    IShellFolder_Release(psfSystemDir);

    cChars = GetCurrentDirectoryA(MAX_PATH, buf);
    if(!cChars)
    {
        skip("Failed to get current directory, skipping tests.\n");
        return;
    }
    if(buf[cChars-1] != '\\') lstrcatA(buf, "\\");

    SHGetDesktopFolder(&psfDesktop);

    /* Attempt BindToObject on files. */

    /* .html */
    lstrcpyA(pathA, buf);
    lstrcatA(pathA, filename_html);
    hfile = CreateFileA(pathA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if(hfile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hfile);
        MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);
        hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, path, NULL, &pidl, NULL);
        ok(hr == S_OK, "Got 0x%08x\n", hr);
        if(SUCCEEDED(hr))
        {
            hr = IShellFolder_BindToObject(psfDesktop, pidl, NULL, &IID_IShellFolder, (void**)&psfChild);
            ok(hr == S_OK ||
               hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP, W2K3 */
               "Got 0x%08x\n", hr);
            if(SUCCEEDED(hr))
            {
                IPersist *pp;
                hr = IShellFolder_QueryInterface(psfChild, &IID_IPersist, (void**)&pp);
                ok(hr == S_OK, "Got 0x%08x\n", hr);
                if(SUCCEEDED(hr))
                {
                    CLSID id;
                    hr = IPersist_GetClassID(pp, &id);
                    ok(hr == S_OK, "Got 0x%08x\n", hr);
                    ok(IsEqualIID(&id, &CLSID_ShellDocObjView), "Unexpected classid %s\n", wine_dbgstr_guid(&id));
                    IPersist_Release(pp);
                }

                IShellFolder_Release(psfChild);
            }
            ILFree(pidl);
        }
        DeleteFileA(pathA);
    }
    else
        win_skip("Failed to create .html testfile.\n");

    /* .txt */
    lstrcpyA(pathA, buf);
    lstrcatA(pathA, filename_txt);
    hfile = CreateFileA(pathA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if(hfile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hfile);
        MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);
        hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, path, NULL, &pidl, NULL);
        ok(hr == S_OK, "Got 0x%08x\n", hr);
        if(SUCCEEDED(hr))
        {
            hr = IShellFolder_BindToObject(psfDesktop, pidl, NULL, &IID_IShellFolder, (void**)&psfChild);
            ok(hr == E_FAIL || /* Vista+ */
               hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP, W2K3 */
               "Got 0x%08x\n", hr);
            if(SUCCEEDED(hr)) IShellFolder_Release(psfChild);
            ILFree(pidl);
        }
        DeleteFileA(pathA);
    }
    else
        win_skip("Failed to create .txt testfile.\n");

    /* .foo */
    lstrcpyA(pathA, buf);
    lstrcatA(pathA, filename_foo);
    hfile = CreateFileA(pathA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if(hfile != INVALID_HANDLE_VALUE)
    {
        CloseHandle(hfile);
        MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);
        hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, path, NULL, &pidl, NULL);
        ok(hr == S_OK, "Got 0x%08x\n", hr);
        if(SUCCEEDED(hr))
        {
            hr = IShellFolder_BindToObject(psfDesktop, pidl, NULL, &IID_IShellFolder, (void**)&psfChild);
            ok(hr == E_FAIL || /* Vista+ */
               hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP, W2K3 */
               "Got 0x%08x\n", hr);
            if(SUCCEEDED(hr)) IShellFolder_Release(psfChild);
            ILFree(pidl);
        }
        DeleteFileA(pathA);
    }
    else
        win_skip("Failed to create .foo testfile.\n");

    /* And on the desktop */
    SHGetSpecialFolderPathA(NULL, pathA, CSIDL_DESKTOP, FALSE);
    lstrcatA(pathA, "\\");
    lstrcatA(pathA, filename_html);
    hfile = CreateFileA(pathA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    CloseHandle(hfile);
    MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);
    hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, path, NULL, &pidl, NULL);
    ok(hr == S_OK, "Got 0x%08x\n", hr);

    hr = IShellFolder_BindToObject(psfDesktop, pidl, NULL, &IID_IShellFolder, (void **)&psfChild);
    ok(hr == S_OK ||
       hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP, W2K3 */
       "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr)) IShellFolder_Release(psfChild);
    ILFree(pidl);
    if(!DeleteFileA(pathA))
        trace("Failed to delete: %d\n", GetLastError());

    SHGetSpecialFolderPathA(NULL, pathA, CSIDL_DESKTOP, FALSE);
    lstrcatA(pathA, "\\");
    lstrcatA(pathA, filename_foo);
    hfile = CreateFileA(pathA, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);

    CloseHandle(hfile);
    MultiByteToWideChar(CP_ACP, 0, pathA, -1, path, MAX_PATH);
    hr = IShellFolder_ParseDisplayName(psfDesktop, NULL, NULL, path, NULL, &pidl, NULL);
    ok(hr == S_OK, "Got 0x%08x\n", hr);

    hr = IShellFolder_BindToObject(psfDesktop, pidl, NULL, &IID_IShellFolder, (void **)&psfChild);
    ok(hr == E_FAIL || /* Vista+ */
       hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND), /* XP, W2K3 */
       "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr)) IShellFolder_Release(psfChild);
    ILFree(pidl);
    DeleteFileA(pathA);

    IShellFolder_Release(psfDesktop);
}