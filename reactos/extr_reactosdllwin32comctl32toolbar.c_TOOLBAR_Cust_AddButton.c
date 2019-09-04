#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  tbInfo; int /*<<< orphan*/  tbHwnd; } ;
struct TYPE_7__ {int iItem; int /*<<< orphan*/  hdr; } ;
struct TYPE_6__ {int /*<<< orphan*/  btn; } ;
typedef  TYPE_1__* PCUSTOMBUTTON ;
typedef  TYPE_2__ NMTOOLBARW ;
typedef  int /*<<< orphan*/  NMHDR ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  CUSTOMBUTTON ;
typedef  TYPE_3__ CUSTDLG_INFO ;

/* Variables and functions */
 TYPE_1__* Alloc (int) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_AVAILBTN_LBOX ; 
 int /*<<< orphan*/  IDC_TOOLBARBTN_LBOX ; 
 int /*<<< orphan*/  LB_DELETESTRING ; 
 int /*<<< orphan*/  LB_GETCOUNT ; 
 int /*<<< orphan*/  LB_GETITEMDATA ; 
 int /*<<< orphan*/  LB_INSERTSTRING ; 
 int /*<<< orphan*/  LB_SETCURSEL ; 
 int /*<<< orphan*/  LB_SETITEMDATA ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TBN_QUERYINSERT ; 
 int /*<<< orphan*/  TBN_TOOLBARCHANGE ; 
 int /*<<< orphan*/  TB_INSERTBUTTONW ; 
 scalar_t__ TOOLBAR_SendNotify (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int,int) ; 

__attribute__((used)) static void TOOLBAR_Cust_AddButton(const CUSTDLG_INFO *custInfo, HWND hwnd, INT nIndexAvail, INT nIndexTo)
{
    NMTOOLBARW nmtb;

    TRACE("Add: nIndexAvail %d, nIndexTo %d\n", nIndexAvail, nIndexTo);

    /* MSDN states that iItem is the index of the button, rather than the
     * command ID as used by every other NMTOOLBAR notification */
    nmtb.iItem = nIndexAvail;
    if (TOOLBAR_SendNotify(&nmtb.hdr, custInfo->tbInfo, TBN_QUERYINSERT))
    {
        PCUSTOMBUTTON btnInfo;
        NMHDR hdr;
        HWND hwndList = GetDlgItem(hwnd, IDC_TOOLBARBTN_LBOX);
        HWND hwndAvail = GetDlgItem(hwnd, IDC_AVAILBTN_LBOX);
        int count = SendMessageW(hwndAvail, LB_GETCOUNT, 0, 0);

        btnInfo = (PCUSTOMBUTTON)SendMessageW(hwndAvail, LB_GETITEMDATA, nIndexAvail, 0);

        if (nIndexAvail != 0) /* index == 0 indicates separator */
        {
            /* remove from 'available buttons' list */
            SendMessageW(hwndAvail, LB_DELETESTRING, nIndexAvail, 0);
            if (nIndexAvail == count-1)
                SendMessageW(hwndAvail, LB_SETCURSEL, nIndexAvail-1 , 0);
            else
                SendMessageW(hwndAvail, LB_SETCURSEL, nIndexAvail , 0);
        }
        else
        {
            PCUSTOMBUTTON btnNew;

            /* duplicate 'separator' button */
            btnNew = Alloc(sizeof(CUSTOMBUTTON));
            *btnNew = *btnInfo;
            btnInfo = btnNew;
        }

        /* insert into 'toolbar button' list */
        SendMessageW(hwndList, LB_INSERTSTRING, nIndexTo, 0);
        SendMessageW(hwndList, LB_SETITEMDATA, nIndexTo, (LPARAM)btnInfo);

        SendMessageW(custInfo->tbHwnd, TB_INSERTBUTTONW, nIndexTo, (LPARAM)&(btnInfo->btn));

        TOOLBAR_SendNotify(&hdr, custInfo->tbInfo, TBN_TOOLBARCHANGE);
    }
}