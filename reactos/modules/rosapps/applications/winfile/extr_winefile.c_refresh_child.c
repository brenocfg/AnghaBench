#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_13__ {int /*<<< orphan*/  hwnd; scalar_t__ cur; } ;
struct TYPE_15__ {scalar_t__ etype; int /*<<< orphan*/  down; } ;
struct TYPE_12__ {TYPE_2__ entry; } ;
struct TYPE_14__ {int /*<<< orphan*/ * root; } ;
struct TYPE_16__ {TYPE_11__ left; int /*<<< orphan*/  hwnd; TYPE_10__ root; int /*<<< orphan*/  sortOrder; TYPE_1__ right; } ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ Entry ;
typedef  TYPE_3__ ChildWnd ;

/* Variables and functions */
 scalar_t__ ET_SHELL ; 
 int /*<<< orphan*/  LB_FINDSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int MAX_PATH ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TF_ALL ; 
 int /*<<< orphan*/  _MAX_DRIVE ; 
 int /*<<< orphan*/  _wsplitpath (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_path (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_path_pidl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_entries (TYPE_11__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* read_tree (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_entry (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_curdir (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void refresh_child(ChildWnd* child)
{
	WCHAR path[MAX_PATH], drv[_MAX_DRIVE+1];
	Entry* entry;
	int idx;

	get_path(child->left.cur, path);
	_wsplitpath(path, drv, NULL, NULL, NULL);

	child->right.root = NULL;

	scan_entry(child, &child->root.entry, 0, child->hwnd);

	if (child->root.entry.etype == ET_SHELL)
	{
		LPITEMIDLIST local_pidl = get_path_pidl(path,child->hwnd);
		if (local_pidl)
			entry = read_tree(&child->root, NULL, local_pidl , drv, child->sortOrder, child->hwnd);
		else
			entry = NULL;
	}
	else
		entry = read_tree(&child->root, path, NULL, drv, child->sortOrder, child->hwnd);

	if (!entry)
		entry = &child->root.entry;

	insert_entries(&child->left, child->root.entry.down, NULL, TF_ALL, 0);

	set_curdir(child, entry, 0, child->hwnd);

	idx = SendMessageW(child->left.hwnd, LB_FINDSTRING, 0, (LPARAM)child->left.cur);
	SendMessageW(child->left.hwnd, LB_SETCURSEL, idx, 0);
}