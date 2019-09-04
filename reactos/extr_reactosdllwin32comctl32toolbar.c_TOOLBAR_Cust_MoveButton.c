#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tbInfo; int /*<<< orphan*/  tbHwnd; } ;
struct TYPE_6__ {int /*<<< orphan*/  hdr; scalar_t__ iItem; } ;
struct TYPE_5__ {int /*<<< orphan*/  btn; } ;
typedef  TYPE_1__* PCUSTOMBUTTON ;
typedef  TYPE_2__ NMTOOLBARW ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_3__ CUSTDLG_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_MOVEDN_BTN ; 
 int /*<<< orphan*/  IDC_MOVEUP_BTN ; 
 int /*<<< orphan*/  IDC_TOOLBARBTN_LBOX ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBN_QUERYINSERT ; 
 int /*<<< orphan*/  TBN_TOOLBARCHANGE ; 
 int /*<<< orphan*/  TB_DELETEBUTTON ; 
 int /*<<< orphan*/  TB_INSERTBUTTONW ; 
 scalar_t__ TOOLBAR_SendNotify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void TOOLBAR_Cust_MoveButton(const CUSTDLG_INFO *custInfo, HWND hwnd, INT nIndexFrom, INT nIndexTo)
{
    NMTOOLBARW nmtb;

	TRACE("index from %d, index to %d\n", nIndexFrom, nIndexTo);

    if (nIndexFrom == nIndexTo)
        return;

    /* MSDN states that iItem is the index of the button, rather than the
     * command ID as used by every other NMTOOLBAR notification */
    nmtb.iItem = nIndexFrom;
    if (TOOLBAR_SendNotify(&nmtb.hdr, custInfo->tbInfo, TBN_QUERYINSERT))
    {
        PCUSTOMBUTTON btnInfo;
        NMHDR hdr;
        HWND hwndList = GetDlgItem(hwnd, IDC_TOOLBARBTN_LBOX);
        int count = SendMessageW(hwndList, LB_GETCOUNT, 0, 0);

        btnInfo = (PCUSTOMBUTTON)SendMessageW(hwndList, LB_GETITEMDATA, nIndexFrom, 0);

        SendMessageW(hwndList, LB_DELETESTRING, nIndexFrom, 0);
        SendMessageW(hwndList, LB_INSERTSTRING, nIndexTo, 0);
        SendMessageW(hwndList, LB_SETITEMDATA, nIndexTo, (LPARAM)btnInfo);
        SendMessageW(hwndList, LB_SETCURSEL, nIndexTo, 0);

        if (nIndexTo <= 0)
            EnableWindow(GetDlgItem(hwnd,IDC_MOVEUP_BTN), FALSE);
        else
            EnableWindow(GetDlgItem(hwnd,IDC_MOVEUP_BTN), TRUE);

        /* last item is always separator, so -2 instead of -1 */
        if (nIndexTo >= (count - 2))
            EnableWindow(GetDlgItem(hwnd,IDC_MOVEDN_BTN), FALSE);
        else
            EnableWindow(GetDlgItem(hwnd,IDC_MOVEDN_BTN), TRUE);

        SendMessageW(custInfo->tbHwnd, TB_DELETEBUTTON, nIndexFrom, 0);
        SendMessageW(custInfo->tbHwnd, TB_INSERTBUTTONW, nIndexTo, (LPARAM)&(btnInfo->btn));

        TOOLBAR_SendNotify(&hdr, custInfo->tbInfo, TBN_TOOLBARCHANGE);
    }
}