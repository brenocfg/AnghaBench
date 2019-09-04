#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int flags; int idResult; } ;
struct TYPE_12__ {scalar_t__ message; int wParam; } ;
struct TYPE_11__ {int state; } ;
typedef  TYPE_1__* PWND ;
typedef  TYPE_2__ MSG ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  TYPE_3__ DIALOGINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DF_END ; 
 int DS_NOIDLEMSG ; 
 int /*<<< orphan*/  DestroyWindow (scalar_t__) ; 
 int /*<<< orphan*/  DispatchMessageW (TYPE_2__*) ; 
 scalar_t__ FALSE ; 
 TYPE_3__* GETDLGINFO (scalar_t__) ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetForegroundWindow () ; 
 scalar_t__ GetKeyState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetMessageW (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsDialogMessageW (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  MSGF_DIALOGBOX ; 
 int /*<<< orphan*/  PM_REMOVE ; 
 int /*<<< orphan*/  PeekMessageW (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PostQuitMessage (int) ; 
 int /*<<< orphan*/  SW_SHOWNORMAL ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_2__*) ; 
 int /*<<< orphan*/  VK_CONTROL ; 
 TYPE_1__* ValidateHwnd (scalar_t__) ; 
 int /*<<< orphan*/  WM_COPY ; 
 int /*<<< orphan*/  WM_ENTERIDLE ; 
 scalar_t__ WM_KEYDOWN ; 
 scalar_t__ WM_QUIT ; 
 scalar_t__ WM_TIMER ; 
 int WNDS_MSGBOX ; 

INT DIALOG_DoDialogBox( HWND hwnd, HWND owner )
{
    DIALOGINFO * dlgInfo;
    MSG msg;
    INT retval;
    BOOL bFirstEmpty;
    PWND pWnd;

    pWnd = ValidateHwnd(hwnd);
    if (!pWnd) return -1;

    if (!(dlgInfo = GETDLGINFO(hwnd))) return -1;

    bFirstEmpty = TRUE;
    if (!(dlgInfo->flags & DF_END)) /* was EndDialog called in WM_INITDIALOG ? */
    {
        for (;;)
        {
            if (!PeekMessageW( &msg, 0, 0, 0, PM_REMOVE ))
            {
                if (bFirstEmpty)
                {
                    /* ShowWindow the first time the queue goes empty */
                    ShowWindow( hwnd, SW_SHOWNORMAL );
                    bFirstEmpty = FALSE;
                }
                if (!(GetWindowLongPtrW( hwnd, GWL_STYLE ) & DS_NOIDLEMSG))
               {
                    /* No message present -> send ENTERIDLE and wait */
                    SendMessageW( owner, WM_ENTERIDLE, MSGF_DIALOGBOX, (LPARAM)hwnd );
                }
                GetMessageW( &msg, 0, 0, 0 );
            }

            if (msg.message == WM_QUIT)
            {
                PostQuitMessage( msg.wParam );
                if (!IsWindow( hwnd )) return 0;
                break;
            }

            /*
             * If the user is pressing Ctrl+C, send a WM_COPY message.
             * Guido Pola, CORE-4829, Is there another way to check if the Dialog is a MessageBox?
             */
            if (msg.message == WM_KEYDOWN &&
                pWnd->state & WNDS_MSGBOX && // Yes!
                GetForegroundWindow() == hwnd)
            {
                if (msg.wParam == L'C' && GetKeyState(VK_CONTROL) < 0)
                    SendMessageW(hwnd, WM_COPY, 0, 0);
            }

            if (!IsWindow( hwnd )) return 0;
            if (!(dlgInfo->flags & DF_END) && !IsDialogMessageW( hwnd, &msg))
            {
                TranslateMessage( &msg );
                DispatchMessageW( &msg );
            }
            if (!IsWindow( hwnd )) return 0;
            if (dlgInfo->flags & DF_END) break;

            if (bFirstEmpty && msg.message == WM_TIMER)
            {
                ShowWindow( hwnd, SW_SHOWNORMAL );
                bFirstEmpty = FALSE;
            }
        }
    }
    retval = dlgInfo->idResult;
    DestroyWindow( hwnd );
    return retval;
}