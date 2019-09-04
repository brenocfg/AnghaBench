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
struct TYPE_3__ {int uNotification; int /*<<< orphan*/  ptCursor; } ;
typedef  int /*<<< orphan*/  POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_1__ DRAGLISTINFO ;
typedef  int /*<<< orphan*/  CUSTDLG_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ChildWindowFromPoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  DL_BEGINDRAG 131 
#define  DL_CANCELDRAG 130 
 int /*<<< orphan*/  DL_COPYCURSOR ; 
#define  DL_DRAGGING 129 
#define  DL_DROPPED 128 
 int /*<<< orphan*/  DL_STOPCURSOR ; 
 int /*<<< orphan*/  DrawInsert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_AVAILBTN_LBOX ; 
 int /*<<< orphan*/  IDC_TOOLBARBTN_LBOX ; 
 int LBItemFromPt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETCURSEL ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TOOLBAR_Cust_MoveButton (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  TOOLBAR_Cust_RemoveButton (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT TOOLBAR_Cust_ToolbarDragListNotification(const CUSTDLG_INFO *custInfo, HWND hwnd,
                                                        const DRAGLISTINFO *pDLI)
{
    HWND hwndList = GetDlgItem(hwnd, IDC_TOOLBARBTN_LBOX);
    switch (pDLI->uNotification)
    {
    case DL_BEGINDRAG:
    {
        INT nCurrentItem = LBItemFromPt(hwndList, pDLI->ptCursor, TRUE);
        INT nCount = SendMessageW(hwndList, LB_GETCOUNT, 0, 0);
        /* no dragging for last item (separator) */
        if (nCurrentItem >= (nCount - 1)) return FALSE;
        return TRUE;
    }
    case DL_DRAGGING:
    {
        INT nCurrentItem = LBItemFromPt(hwndList, pDLI->ptCursor, TRUE);
        INT nCount = SendMessageW(hwndList, LB_GETCOUNT, 0, 0);
        /* no dragging past last item (separator) */
        if ((nCurrentItem >= 0) && (nCurrentItem < (nCount - 1)))
        {
            DrawInsert(hwnd, hwndList, nCurrentItem);
            /* FIXME: native uses "move button" cursor */
            return DL_COPYCURSOR;
        }

        /* not over toolbar buttons list */
        if (nCurrentItem < 0)
        {
            POINT ptWindow = pDLI->ptCursor;
            HWND hwndListAvail = GetDlgItem(hwnd, IDC_AVAILBTN_LBOX);
            MapWindowPoints(NULL, hwnd, &ptWindow, 1);
            /* over available buttons list? */
            if (ChildWindowFromPoint(hwnd, ptWindow) == hwndListAvail)
                /* FIXME: native uses "move button" cursor */
                return DL_COPYCURSOR;
        }
        /* clear drag arrow */
        DrawInsert(hwnd, hwndList, -1);
        return DL_STOPCURSOR;
    }
    case DL_DROPPED:
    {
        INT nIndexTo = LBItemFromPt(hwndList, pDLI->ptCursor, TRUE);
        INT nIndexFrom = SendMessageW(hwndList, LB_GETCURSEL, 0, 0);
        INT nCount = SendMessageW(hwndList, LB_GETCOUNT, 0, 0);
        if ((nIndexTo >= 0) && (nIndexTo < (nCount - 1)))
        {
            /* clear drag arrow */
            DrawInsert(hwnd, hwndList, -1);
            /* move item */
            TOOLBAR_Cust_MoveButton(custInfo, hwnd, nIndexFrom, nIndexTo);
        }
        /* not over toolbar buttons list */
        if (nIndexTo < 0)
        {
            POINT ptWindow = pDLI->ptCursor;
            HWND hwndListAvail = GetDlgItem(hwnd, IDC_AVAILBTN_LBOX);
            MapWindowPoints(NULL, hwnd, &ptWindow, 1);
            /* over available buttons list? */
            if (ChildWindowFromPoint(hwnd, ptWindow) == hwndListAvail)
                TOOLBAR_Cust_RemoveButton(custInfo, hwnd, nIndexFrom);
        }
        break;
    }
    case DL_CANCELDRAG:
        /* Clear drag arrow */
        DrawInsert(hwnd, hwndList, -1);
        break;
    }

    return 0;
}