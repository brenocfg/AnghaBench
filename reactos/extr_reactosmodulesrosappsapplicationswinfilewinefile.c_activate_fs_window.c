#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_6__ {scalar_t__ hmdiclient; } ;
struct TYPE_4__ {int /*<<< orphan*/  fs; } ;
struct TYPE_5__ {TYPE_1__ root; } ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  scalar_t__ HWND ;
typedef  TYPE_2__ ChildWnd ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWLP_USERDATA ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 scalar_t__ GetNextWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__ Globals ; 
 scalar_t__ IsIconic (scalar_t__) ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MDIACTIVATE ; 
 int /*<<< orphan*/  lstrcmpiW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL activate_fs_window(LPCWSTR filesys)
{
	HWND child_wnd;

        /* search for an already open window of the given file system name */
	for(child_wnd=GetNextWindow(Globals.hmdiclient,GW_CHILD); child_wnd; child_wnd=GetNextWindow(child_wnd, GW_HWNDNEXT)) {
		ChildWnd* child = (ChildWnd*) GetWindowLongPtrW(child_wnd, GWLP_USERDATA);

		if (child) {
			if (!lstrcmpiW(child->root.fs, filesys)) {
				SendMessageW(Globals.hmdiclient, WM_MDIACTIVATE, (WPARAM)child_wnd, 0);

				if (IsIconic(child_wnd))
					ShowWindow(child_wnd, SW_SHOWNORMAL);

				return TRUE;
			}
		}
	}

	return FALSE;
}