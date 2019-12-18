#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int m_iItemSelected; int /*<<< orphan*/  m_hWnd; } ;
typedef  TYPE_1__ WF_IDropTarget ;
struct TYPE_9__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_8__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_2__ POINTL ;
typedef  TYPE_3__ POINT ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DSRectItem (int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDCW_LISTBOX ; 
 int /*<<< orphan*/  IDCW_TREELISTBOX ; 
 int /*<<< orphan*/  LB_ITEMFROMPOINT ; 
 int /*<<< orphan*/  MAKELPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ RectTreeItem (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/  ScreenToClient (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int SendMessage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 

void PaintRectItem(WF_IDropTarget *This, POINTL *ppt)
{
	HWND hwndLB;
	DWORD iItem;
	POINT pt;
	BOOL fTree;
	
	// could be either tree control or directory list box
	hwndLB = GetDlgItem(This->m_hWnd, IDCW_LISTBOX);
	fTree = FALSE;
	if (hwndLB == NULL)
	{
		hwndLB = GetDlgItem(This->m_hWnd, IDCW_TREELISTBOX);
		fTree = TRUE;

		if (hwndLB == NULL)
			return;
	}

	if (ppt != NULL)
	{
		pt.x = ppt->x;
		pt.y = ppt->y;
		ScreenToClient(hwndLB, &pt);
	
		iItem = SendMessage(hwndLB, LB_ITEMFROMPOINT, 0, MAKELPARAM(pt.x, pt.y));
		iItem &= 0xffff;
		if (This->m_iItemSelected != -1 && This->m_iItemSelected == iItem)
			return;
	}

	// unpaint old item
	if (This->m_iItemSelected != -1)
	{
	    if (fTree)
			RectTreeItem(hwndLB, This->m_iItemSelected, FALSE);
		else
			DSRectItem(hwndLB, This->m_iItemSelected, FALSE, FALSE);

		This->m_iItemSelected = (DWORD)-1;
	}

	// if new item, paint it.
	if (ppt != NULL)
	{
	    if (fTree)
		{
			if (RectTreeItem(hwndLB, iItem, TRUE))
				This->m_iItemSelected = iItem;
		}
		else
		{
			if (DSRectItem(hwndLB, iItem, TRUE, FALSE))
				This->m_iItemSelected = iItem;
		}
	}
}