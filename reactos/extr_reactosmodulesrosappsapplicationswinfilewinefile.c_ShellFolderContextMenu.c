#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_3__ {int cbSize; scalar_t__ hIcon; scalar_t__ dwHotKey; int /*<<< orphan*/  nShow; int /*<<< orphan*/ * lpDirectory; int /*<<< orphan*/ * lpParameters; scalar_t__ lpVerb; int /*<<< orphan*/  hwnd; scalar_t__ fMask; } ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  scalar_t__ LPCSTR ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  scalar_t__ INT_PTR ;
typedef  int /*<<< orphan*/  IContextMenu ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ HMENU ;
typedef  TYPE_1__ CMINVOKECOMMANDINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CMF_NORMAL ; 
 scalar_t__ CreatePopupMenu () ; 
 int /*<<< orphan*/ * CtxMenu_query_interfaces (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CtxMenu_reset () ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ FCIDM_SHVIEWFIRST ; 
 int /*<<< orphan*/  FCIDM_SHVIEWLAST ; 
 int /*<<< orphan*/  IContextMenu_InvokeCommand (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  IContextMenu_QueryContextMenu (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IContextMenu_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IContextMenu ; 
 int /*<<< orphan*/  IShellFolder_GetUIObjectOf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int TPM_LEFTALIGN ; 
 int TPM_RETURNCMD ; 
 int TPM_RIGHTBUTTON ; 
 scalar_t__ TRUE ; 
 scalar_t__ TrackPopupMenu (scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT ShellFolderContextMenu(IShellFolder* shell_folder, HWND hwndParent, int cidl, LPCITEMIDLIST* apidl, int x, int y)
{
	IContextMenu* pcm;
	BOOL executed = FALSE;

	HRESULT hr = IShellFolder_GetUIObjectOf(shell_folder, hwndParent, cidl, apidl, &IID_IContextMenu, NULL, (LPVOID*)&pcm);

	if (SUCCEEDED(hr)) {
		HMENU hmenu = CreatePopupMenu();

		pcm = CtxMenu_query_interfaces(pcm);

		if (hmenu) {
			hr = IContextMenu_QueryContextMenu(pcm, hmenu, 0, FCIDM_SHVIEWFIRST, FCIDM_SHVIEWLAST, CMF_NORMAL);

			if (SUCCEEDED(hr)) {
				UINT idCmd = TrackPopupMenu(hmenu, TPM_LEFTALIGN|TPM_RETURNCMD|TPM_RIGHTBUTTON, x, y, 0, hwndParent, NULL);

				CtxMenu_reset();

				if (idCmd) {
				  CMINVOKECOMMANDINFO cmi;

				  cmi.cbSize = sizeof(CMINVOKECOMMANDINFO);
				  cmi.fMask = 0;
				  cmi.hwnd = hwndParent;
				  cmi.lpVerb = (LPCSTR)(INT_PTR)(idCmd - FCIDM_SHVIEWFIRST);
				  cmi.lpParameters = NULL;
				  cmi.lpDirectory = NULL;
				  cmi.nShow = SW_SHOWNORMAL;
				  cmi.dwHotKey = 0;
				  cmi.hIcon = 0;

				  hr = IContextMenu_InvokeCommand(pcm, &cmi);
					executed = TRUE;
				}
			} else
				CtxMenu_reset();
		}

		IContextMenu_Release(pcm);
	}

	return FAILED(hr)? hr: executed? S_OK: S_FALSE;
}