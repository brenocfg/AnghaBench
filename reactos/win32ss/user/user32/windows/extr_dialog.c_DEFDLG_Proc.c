#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int UINT ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  hUserFont; int /*<<< orphan*/  idResult; int /*<<< orphan*/  hMenu; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int LRESULT ;
typedef  int /*<<< orphan*/  LPPOINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  TYPE_1__ DIALOGINFO ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CLICKED ; 
 int /*<<< orphan*/  CB_SHOWDROPDOWN ; 
 int /*<<< orphan*/  DC_HASDEFID ; 
 int /*<<< orphan*/  DEFDLG_FindDefButton (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_Reposition (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_RestoreFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_SaveFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_SetDefButton (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_SetDefId (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEFDLG_SetFocus (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DF_DIALOGACTIVE ; 
 int DF_END ; 
 int /*<<< orphan*/  DIALOG_FindMsgDestination (int /*<<< orphan*/ ) ; 
#define  DM_GETDEFID 141 
#define  DM_REPOSITION 140 
#define  DM_SETDEFID 139 
 int /*<<< orphan*/  DPtoLP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  DWLP_ROS_DIALOGINFO ; 
 int DefWindowProcA (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DestroyMenu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetControlColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgCtrlID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFocus () ; 
 int /*<<< orphan*/  GetNextDlgTabItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetParent (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  IDCANCEL ; 
 int MAKELONG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEWPARAM (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserSetThreadState (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NtUserxSetDialogPointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
#define  WM_ACTIVATE 138 
#define  WM_CLOSE 137 
 int /*<<< orphan*/  WM_COMMAND ; 
 int /*<<< orphan*/  WM_CTLCOLORDLG ; 
#define  WM_ENTERMENULOOP 136 
#define  WM_ERASEBKGND 135 
#define  WM_GETFONT 134 
#define  WM_LBUTTONDOWN 133 
#define  WM_NCDESTROY 132 
#define  WM_NCLBUTTONDOWN 131 
#define  WM_NEXTDLGCTL 130 
#define  WM_SETFOCUS 129 
#define  WM_SHOWWINDOW 128 

__attribute__((used)) static LRESULT DEFDLG_Proc( HWND hwnd, UINT msg, WPARAM wParam,
                            LPARAM lParam, DIALOGINFO *dlgInfo )
{
    switch(msg)
    {
        case WM_ERASEBKGND:
        {
            HBRUSH brush = GetControlColor( hwnd, hwnd, (HDC)wParam, WM_CTLCOLORDLG);
            if (brush)
            {
                RECT rect;
                HDC hdc = (HDC)wParam;
                GetClientRect( hwnd, &rect );
                DPtoLP( hdc, (LPPOINT)&rect, 2 );
                FillRect( hdc, &rect, brush );
            }
            return 1;
        }
        case WM_NCDESTROY:
//// ReactOS
            if ((dlgInfo = (DIALOGINFO *)SetWindowLongPtrW( hwnd, DWLP_ROS_DIALOGINFO, 0 )))
            {
                if (dlgInfo->hUserFont) DeleteObject( dlgInfo->hUserFont );
                if (dlgInfo->hMenu) DestroyMenu( dlgInfo->hMenu );
                HeapFree( GetProcessHeap(), 0, dlgInfo );
                NtUserSetThreadState(0,DF_DIALOGACTIVE);
                NtUserxSetDialogPointer( hwnd, 0 );
            }
             /* Window clean-up */
            return DefWindowProcA( hwnd, msg, wParam, lParam );

        case WM_SHOWWINDOW:
            if (!wParam) DEFDLG_SaveFocus( hwnd );
            return DefWindowProcA( hwnd, msg, wParam, lParam );

        case WM_ACTIVATE:
            { // ReactOS
               DWORD dwSetFlag;
               HWND hwndparent = DIALOG_FindMsgDestination( hwnd );
               // if WA_CLICK/ACTIVE ? set dialog is active.
               dwSetFlag = wParam ? DF_DIALOGACTIVE : 0;
               if (hwndparent != hwnd) NtUserSetThreadState(dwSetFlag, DF_DIALOGACTIVE);
            }
            if (wParam) DEFDLG_RestoreFocus( hwnd, TRUE );
            else DEFDLG_SaveFocus( hwnd );
            return 0;

        case WM_SETFOCUS:
            DEFDLG_RestoreFocus( hwnd, FALSE );
            return 0;

        case DM_SETDEFID:
            if (dlgInfo && !(dlgInfo->flags & DF_END))
                DEFDLG_SetDefId( hwnd, dlgInfo, wParam );
            return 1;

        case DM_GETDEFID:
            if (dlgInfo && !(dlgInfo->flags & DF_END))
            {
                HWND hwndDefId;
                if (dlgInfo->idResult)
                    return MAKELONG( dlgInfo->idResult, DC_HASDEFID );
                if ((hwndDefId = DEFDLG_FindDefButton( hwnd )))
                    return MAKELONG( GetDlgCtrlID( hwndDefId ), DC_HASDEFID);
            }
            return 0;

#ifdef __REACTOS__
        case DM_REPOSITION:
            DEFDLG_Reposition(hwnd);
            return 0;
#endif
        case WM_NEXTDLGCTL:
            if (dlgInfo)
            {
                HWND hwndDest = (HWND)wParam;
                if (!lParam)
                    hwndDest = GetNextDlgTabItem(hwnd, GetFocus(), wParam);
                if (hwndDest) DEFDLG_SetFocus( hwndDest );
                DEFDLG_SetDefButton( hwnd, dlgInfo, hwndDest );
            }
            return 0;

        case WM_ENTERMENULOOP:
        case WM_LBUTTONDOWN:
        case WM_NCLBUTTONDOWN:
            {
                HWND hwndFocus = GetFocus();
                if (hwndFocus)
                {
                    /* always make combo box hide its listbox control */
                    if (!SendMessageW( hwndFocus, CB_SHOWDROPDOWN, FALSE, 0 ))
                        SendMessageW( GetParent(hwndFocus), CB_SHOWDROPDOWN, FALSE, 0 );
                }
            }
            return DefWindowProcA( hwnd, msg, wParam, lParam );

        case WM_GETFONT:
            return dlgInfo ? (LRESULT)dlgInfo->hUserFont : 0;

        case WM_CLOSE:
            PostMessageA( hwnd, WM_COMMAND, MAKEWPARAM(IDCANCEL, BN_CLICKED),
                            (LPARAM)GetDlgItem( hwnd, IDCANCEL ) );
            return 0;
    }
    return 0;
}