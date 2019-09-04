#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  char WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {TYPE_4__ IExplorerBrowserEvents_iface; } ;
typedef  int /*<<< orphan*/  LPWSTR ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IFolderView ;
typedef  int /*<<< orphan*/  IExplorerBrowser ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EBO_ALWAYSNAVIGATE ; 
 int /*<<< orphan*/  EBO_NAVIGATEONCE ; 
 int /*<<< orphan*/  ERROR_BUSY ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 scalar_t__ IExplorerBrowser_Advise (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IExplorerBrowser_BrowseToIDList (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IExplorerBrowser_BrowseToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IExplorerBrowser_Destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ IExplorerBrowser_GetCurrentView (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IExplorerBrowser_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IExplorerBrowser_SetOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IExplorerBrowser_Unadvise (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ IFolderView_GetFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IFolderView_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IFolderView ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItem_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryW (char*) ; 
 int SBSP_ABSOLUTE ; 
 int SBSP_DEFBROWSER ; 
 int SBSP_EXPLOREMODE ; 
 int SBSP_NAVIGATEBACK ; 
 int SBSP_NAVIGATEFORWARD ; 
 int /*<<< orphan*/  SBSP_NEWBROWSER ; 
 int SBSP_OPENMODE ; 
 int SBSP_PARENT ; 
 int SBSP_RELATIVE ; 
 int SBSP_SAMEBROWSER ; 
 scalar_t__ SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 TYPE_1__ ebev ; 
 int /*<<< orphan*/  ebevents ; 
 int /*<<< orphan*/  ebrowser_initialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ebrowser_instantiate (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char*) ; 
 int /*<<< orphan*/  myPathAddBackslashW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pSHCreateShellItem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  pSHParseDisplayName (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_msgs () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_browse_pidl (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_browse_pidl_sb (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void test_navigation(void)
{
    IExplorerBrowser *peb, *peb2;
    IFolderView *pfv;
    IShellItem *psi;
    IShellFolder *psf;
    LPITEMIDLIST pidl_current, pidl_child;
    DWORD cookie, cookie2;
    HRESULT hr;
    LONG lres;
    WCHAR current_path[MAX_PATH];
    WCHAR child_path[MAX_PATH];
    static const WCHAR testfolderW[] =
        {'w','i','n','e','t','e','s','t','f','o','l','d','e','r','\0'};

    ok(pSHParseDisplayName != NULL, "pSHParseDisplayName unexpectedly missing.\n");
    ok(pSHCreateShellItem != NULL, "pSHCreateShellItem unexpectedly missing.\n");

    GetCurrentDirectoryW(MAX_PATH, current_path);
    if(!current_path[0])
    {
        skip("Failed to create test-directory.\n");
        return;
    }

    lstrcpyW(child_path, current_path);
    myPathAddBackslashW(child_path);
    lstrcatW(child_path, testfolderW);

    CreateDirectoryW(child_path, NULL);

    pSHParseDisplayName(current_path, NULL, &pidl_current, 0, NULL);
    pSHParseDisplayName(child_path, NULL, &pidl_child, 0, NULL);

    ebrowser_instantiate(&peb);
    ebrowser_initialize(peb);

    ebrowser_instantiate(&peb2);
    ebrowser_initialize(peb2);

    /* Set up our IExplorerBrowserEvents implementation */
    ebev.IExplorerBrowserEvents_iface.lpVtbl = &ebevents;

    IExplorerBrowser_Advise(peb, &ebev.IExplorerBrowserEvents_iface, &cookie);
    IExplorerBrowser_Advise(peb2, &ebev.IExplorerBrowserEvents_iface, &cookie2);

    /* These should all fail */
    test_browse_pidl(peb, &ebev, 0, SBSP_ABSOLUTE | SBSP_RELATIVE, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_ABSOLUTE | SBSP_RELATIVE, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_ABSOLUTE, E_INVALIDARG, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_ABSOLUTE, E_INVALIDARG, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_RELATIVE, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_RELATIVE, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_PARENT, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_PARENT, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEFORWARD, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEFORWARD, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEBACK, E_FAIL, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEBACK, E_FAIL, 0, 0, 0, 0);

    /* "The first browse is synchronous" */
    test_browse_pidl(peb, &ebev, pidl_child, SBSP_ABSOLUTE, S_OK, 1, 1, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, pidl_child, SBSP_ABSOLUTE, S_OK, 1, 1, 0, 1);

    /* Navigate empty history */
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEFORWARD, S_OK, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEFORWARD, S_OK, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEBACK, S_OK, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEBACK, S_OK, 0, 0, 0, 0);

    /* Navigate history */
    test_browse_pidl(peb, &ebev, 0, SBSP_PARENT, S_OK, 1, 1, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_PARENT, S_OK, 1, 1, 0, 1);
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEBACK, S_OK, 1, 1, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEBACK, S_OK, 1, 1, 0, 1);
    test_browse_pidl(peb, &ebev, 0, SBSP_NAVIGATEFORWARD, S_OK, 1, 1, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_NAVIGATEFORWARD, S_OK, 1, 1, 0, 1);
    test_browse_pidl(peb, &ebev, 0, SBSP_ABSOLUTE, S_OK, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, 0, SBSP_ABSOLUTE, S_OK, 0, 0, 0, 0);

    /* Relative navigation */
    test_browse_pidl(peb, &ebev, pidl_current, SBSP_ABSOLUTE, S_OK, 1, 0, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, pidl_current, SBSP_ABSOLUTE, S_OK, 1, 0, 0, 1);

    hr = IExplorerBrowser_GetCurrentView(peb, &IID_IFolderView, (void**)&pfv);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr))
    {
        LPITEMIDLIST pidl_relative;

        hr = IFolderView_GetFolder(pfv, &IID_IShellFolder, (void**)&psf);
        ok(hr == S_OK, "Got 0x%08x\n", hr);
        hr = IShellFolder_ParseDisplayName(psf, NULL, NULL, (LPWSTR)testfolderW,
                                           NULL, &pidl_relative, NULL);
        ok(hr == S_OK, "Got 0x%08x\n", hr);

        /* Browsing to another location here before using the
         * pidl_relative would make ExplorerBrowser in Windows 7 show a
         * not-available dialog. Also, passing a relative pidl without
         * specifying SBSP_RELATIVE makes it look for the pidl on the
         * desktop
         */

        test_browse_pidl(peb, &ebev, pidl_relative, SBSP_RELATIVE, S_OK, 1, 1, 0, 1);
        test_browse_pidl_sb(peb2, &ebev, pidl_relative, SBSP_RELATIVE, S_OK, 1, 1, 0, 1);

        ILFree(pidl_relative);
        IShellFolder_Release(psf);
        IFolderView_Release(pfv);
    }

    /* misc **/
    test_browse_pidl(peb, &ebev, NULL, SBSP_ABSOLUTE, S_OK, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, NULL, SBSP_ABSOLUTE, S_OK, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, NULL, SBSP_DEFBROWSER, S_OK, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, NULL, SBSP_DEFBROWSER, S_OK, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, pidl_current, SBSP_SAMEBROWSER, S_OK, 1, 1, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, pidl_current, SBSP_SAMEBROWSER, S_OK, 1, 1, 0, 1);
    test_browse_pidl(peb, &ebev, pidl_current, SBSP_SAMEBROWSER, S_OK, 1, 0, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, pidl_current, SBSP_SAMEBROWSER, S_OK, 1, 0, 0, 1);

    test_browse_pidl(peb, &ebev, pidl_current, SBSP_EXPLOREMODE, E_INVALIDARG, 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, pidl_current, SBSP_EXPLOREMODE, E_INVALIDARG, 0, 0, 0, 0);
    test_browse_pidl(peb, &ebev, pidl_current, SBSP_OPENMODE, S_OK, 1, 0, 0, 1);
    test_browse_pidl_sb(peb2, &ebev, pidl_current, SBSP_OPENMODE, S_OK, 1, 0, 0, 1);

    /* SBSP_NEWBROWSER will return E_INVALIDARG, claims MSDN, but in
     * reality it works as one would expect (Windows 7 only?).
     */
    if(0)
    {
        IExplorerBrowser_BrowseToIDList(peb, NULL, SBSP_NEWBROWSER);
    }

    hr = IExplorerBrowser_Unadvise(peb, cookie);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    IExplorerBrowser_Destroy(peb);
    process_msgs();
    hr = IExplorerBrowser_Unadvise(peb2, cookie2);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    IExplorerBrowser_Destroy(peb2);
    process_msgs();

    /* Attempt browsing after destroyed */
    test_browse_pidl(peb, &ebev, pidl_child, SBSP_ABSOLUTE, HRESULT_FROM_WIN32(ERROR_BUSY), 0, 0, 0, 0);
    test_browse_pidl_sb(peb2, &ebev, pidl_child, SBSP_ABSOLUTE, HRESULT_FROM_WIN32(ERROR_BUSY), 0, 0, 0, 0);

    lres = IExplorerBrowser_Release(peb);
    ok(lres == 0, "Got lres %d\n", lres);
    lres = IExplorerBrowser_Release(peb2);
    ok(lres == 0, "Got lres %d\n", lres);

    /******************************************/
    /* Test some options that affect browsing */

    ebrowser_instantiate(&peb);
    hr = IExplorerBrowser_Advise(peb, &ebev.IExplorerBrowserEvents_iface, &cookie);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    hr = IExplorerBrowser_SetOptions(peb, EBO_NAVIGATEONCE);
    ok(hr == S_OK, "got (0x%08x)\n", hr);
    ebrowser_initialize(peb);

    test_browse_pidl(peb, &ebev, pidl_current, 0, S_OK, 1, 1, 0, 1);
    test_browse_pidl(peb, &ebev, pidl_current, 0, E_FAIL, 0, 0, 0, 0);

    hr = IExplorerBrowser_SetOptions(peb, 0);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    test_browse_pidl(peb, &ebev, pidl_current, 0, S_OK, 1, 0, 0, 1);
    test_browse_pidl(peb, &ebev, pidl_current, 0, S_OK, 1, 0, 0, 1);

    /* Difference in behavior lies where? */
    hr = IExplorerBrowser_SetOptions(peb, EBO_ALWAYSNAVIGATE);
    ok(hr == S_OK, "got (0x%08x)\n", hr);

    test_browse_pidl(peb, &ebev, pidl_current, 0, S_OK, 1, 0, 0, 1);
    test_browse_pidl(peb, &ebev, pidl_current, 0, S_OK, 1, 0, 0, 1);

    hr = IExplorerBrowser_Unadvise(peb, cookie);
    ok(hr == S_OK, "Got 0x%08x\n", hr);

    IExplorerBrowser_Destroy(peb);
    lres = IExplorerBrowser_Release(peb);
    ok(lres == 0, "Got lres %d\n", lres);

    /* BrowseToObject tests */
    ebrowser_instantiate(&peb);
    ebrowser_initialize(peb);

    /* Browse to the desktop by passing an IShellFolder */
    hr = SHGetDesktopFolder(&psf);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr))
    {
        hr = IExplorerBrowser_BrowseToObject(peb, (IUnknown*)psf, SBSP_DEFBROWSER);
        ok(hr == S_OK, "got (0x%08x)\n", hr);
        if(hr == S_OK) process_msgs();

        IShellFolder_Release(psf);
    }

    /* Browse to the current directory by passing a ShellItem */
    hr = pSHCreateShellItem(NULL, NULL, pidl_current, &psi);
    ok(hr == S_OK, "Got 0x%08x\n", hr);
    if(SUCCEEDED(hr))
    {
        hr = IExplorerBrowser_BrowseToObject(peb, (IUnknown*)psi, SBSP_DEFBROWSER);
        ok(hr == S_OK, "got (0x%08x)\n", hr);
        process_msgs();

        IShellItem_Release(psi);
    }

    IExplorerBrowser_Destroy(peb);
    lres = IExplorerBrowser_Release(peb);
    ok(lres == 0, "Got lres %d\n", lres);

    /* Cleanup */
    RemoveDirectoryW(child_path);
    ILFree(pidl_current);
    ILFree(pidl_child);
}