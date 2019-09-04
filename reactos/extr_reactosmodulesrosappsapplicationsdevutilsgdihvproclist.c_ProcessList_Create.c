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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_3__ {int mask; char* pszText; int cx; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_1__ LVCOLUMN ;
typedef  int /*<<< orphan*/  HWND ;

/* Variables and functions */
 int /*<<< orphan*/  LVCFMT_LEFT ; 
 int LVCF_FMT ; 
 int LVCF_TEXT ; 
 int LVCF_WIDTH ; 
 int /*<<< orphan*/  ListView_InsertColumn (int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ProcessList_Update (int /*<<< orphan*/ ) ; 

VOID
ProcessList_Create(HWND hListCtrl)
{
	LVCOLUMN column;

	column.mask = LVCF_TEXT|LVCF_FMT|LVCF_WIDTH;
	column.fmt = LVCFMT_LEFT;

	column.pszText = L"Process";
	column.cx = 90;
	(void)ListView_InsertColumn(hListCtrl, 0, &column);

	column.pszText = L"ProcessID";
	column.cx = 90;
	(void)ListView_InsertColumn(hListCtrl, 1, &column);
	ProcessList_Update(hListCtrl);
}