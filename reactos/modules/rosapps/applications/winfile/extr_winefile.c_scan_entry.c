#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_15__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_12__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_14__ {int /*<<< orphan*/  header_wdths_ok; TYPE_4__ right; int /*<<< orphan*/  filter_flags; int /*<<< orphan*/  filter_pattern; int /*<<< orphan*/  sortOrder; TYPE_1__ left; } ;
struct TYPE_13__ {scalar_t__ level; scalar_t__ etype; int /*<<< orphan*/  down; } ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HCURSOR ;
typedef  TYPE_2__ Entry ;
typedef  TYPE_3__ ChildWnd ;

/* Variables and functions */
 scalar_t__ ET_SHELL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IDC_WAIT ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_RESETCONTENT ; 
 int /*<<< orphan*/  LoadCursorW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  calc_widths (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_entries (TYPE_2__*) ; 
 int /*<<< orphan*/  get_path (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  insert_entries (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_directory (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_header (TYPE_4__*) ; 

__attribute__((used)) static void scan_entry(ChildWnd* child, Entry* entry, int idx, HWND hwnd)
{
	WCHAR path[MAX_PATH];
	HCURSOR old_cursor = SetCursor(LoadCursorW(0, (LPCWSTR)IDC_WAIT));

	/* delete sub entries in left pane */
	for(;;) {
		LRESULT res = SendMessageW(child->left.hwnd, LB_GETITEMDATA, idx+1, 0);
		Entry* sub = (Entry*) res;

		if (res==LB_ERR || !sub || sub->level<=entry->level)
			break;

		SendMessageW(child->left.hwnd, LB_DELETESTRING, idx+1, 0);
	}

	/* empty right pane */
	SendMessageW(child->right.hwnd, LB_RESETCONTENT, 0, 0);

	/* release memory */
	free_entries(entry);

	/* read contents from disk */
	if (entry->etype == ET_SHELL)
	{
		read_directory(entry, NULL, child->sortOrder, hwnd);
	}
	else
	{
		get_path(entry, path);
		read_directory(entry, path, child->sortOrder, hwnd);
	}

	/* insert found entries in right pane */
	insert_entries(&child->right, entry->down, child->filter_pattern, child->filter_flags, -1);
	calc_widths(&child->right, FALSE);
	set_header(&child->right);

	child->header_wdths_ok = FALSE;

	SetCursor(old_cursor);
}