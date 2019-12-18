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
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IExplorerBrowser ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CSIDL_DESKTOP ; 
 int /*<<< orphan*/  IExplorerBrowser_BrowseToIDList (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SHGetSpecialFolderLocation (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hwnd ; 

__attribute__((used)) static HRESULT ebrowser_browse_to_desktop(IExplorerBrowser *peb)
{
    LPITEMIDLIST pidl_desktop;
    HRESULT hr;
    SHGetSpecialFolderLocation (hwnd, CSIDL_DESKTOP, &pidl_desktop);
    hr = IExplorerBrowser_BrowseToIDList(peb, pidl_desktop, 0);
    ILFree(pidl_desktop);
    return hr;
}