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
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IContextMenu ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  Cleanup () ; 
 int /*<<< orphan*/  CreateFilesFolders () ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 int /*<<< orphan*/  IContextMenu_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IContextMenu ; 
 int /*<<< orphan*/  IID_IShellFolder ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 scalar_t__ IShellFolder_GetUIObjectOf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IShellFolder_ParseDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 scalar_t__ SHBindToParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_contextmenu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_GetUIObject(void)
{
    IShellFolder *psf_desktop;
    IContextMenu *pcm;
    LPITEMIDLIST pidl;
    HRESULT hr;
    WCHAR path[MAX_PATH];
    const WCHAR filename[] =
        {'\\','t','e','s','t','d','i','r','\\','t','e','s','t','1','.','t','x','t',0};
    LPCITEMIDLIST pidl_child;
    IShellFolder *psf;

    GetCurrentDirectoryW(MAX_PATH, path);
    if (!path[0])
    {
        skip("GetCurrentDirectoryW returned an empty string.\n");
        return;
    }
    lstrcatW(path, filename);
    SHGetDesktopFolder(&psf_desktop);

    CreateFilesFolders();

    hr = IShellFolder_ParseDisplayName(psf_desktop, NULL, NULL, path, NULL, &pidl, 0);
    ok(hr == S_OK, "Got 0x%08x\n", hr);

    hr = SHBindToParent(pidl, &IID_IShellFolder, (void **)&psf, &pidl_child);
    ok(hr == S_OK, "Failed to bind to folder, hr %#x.\n", hr);

    /* Item menu */
    hr = IShellFolder_GetUIObjectOf(psf, NULL, 1, &pidl_child, &IID_IContextMenu, NULL, (void **)&pcm);
    ok(hr == S_OK, "GetUIObjectOf() failed, hr %#x.\n", hr);
    test_contextmenu(pcm, FALSE);
    IContextMenu_Release(pcm);

    /* Background menu */
    hr = IShellFolder_GetUIObjectOf(psf_desktop, NULL, 0, NULL, &IID_IContextMenu, NULL, (void **)&pcm);
    ok(hr == S_OK, "GetUIObjectOf() failed, hr %#x.\n", hr);
    test_contextmenu(pcm, TRUE);
    IContextMenu_Release(pcm);

    IShellFolder_Release(psf);
    ILFree(pidl);

    IShellFolder_Release(psf_desktop);
    Cleanup();
}