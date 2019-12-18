#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ level; int /*<<< orphan*/  expanded; } ;
struct TYPE_5__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ Pane ;
typedef  scalar_t__ LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_2__ Entry ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 scalar_t__ LB_ERR ; 
 int /*<<< orphan*/  LB_FINDSTRING ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  SW_SHOW ; 
 void* SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collapse_entry(Pane* pane, Entry* dir)
{
        int idx;

        if (!dir) return;
        idx = SendMessageW(pane->hwnd, LB_FINDSTRING, 0, (LPARAM)dir);

	ShowWindow(pane->hwnd, SW_HIDE);

	/* hide sub entries */
	for(;;) {
		LRESULT res = SendMessageW(pane->hwnd, LB_GETITEMDATA, idx+1, 0);
		Entry* sub = (Entry*) res;

		if (res==LB_ERR || !sub || sub->level<=dir->level)
			break;

		SendMessageW(pane->hwnd, LB_DELETESTRING, idx+1, 0);
	}

	dir->expanded = FALSE;

	ShowWindow(pane->hwnd, SW_SHOW);
}