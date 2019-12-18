#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  buffer ;
typedef  char WPARAM ;
typedef  char WCHAR ;
typedef  char* LPWSTR ;
typedef  int INT ;
typedef  scalar_t__ HWND ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_CLICK ; 
 int BS_GROUPBOX ; 
 int DLGC_BUTTON ; 
 int DLGC_STATIC ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GW_CHILD ; 
 int /*<<< orphan*/  GW_HWNDNEXT ; 
 scalar_t__ GetParent (scalar_t__) ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ GetWindowTextW (scalar_t__,char*,int) ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,char,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 
 int /*<<< orphan*/  WM_NEXTDLGCTL ; 
 int WS_DISABLED ; 
 int WS_VISIBLE ; 
 char* strchrW (char*,char) ; 
 scalar_t__ toupperW (char) ; 

__attribute__((used)) static BOOL DIALOG_IsAccelerator( HWND hwnd, HWND hwndDlg, WPARAM wParam )
{
    HWND hwndControl = hwnd;
    HWND hwndNext;
    INT dlgCode;
    WCHAR buffer[128];

    do
    {
        DWORD style = GetWindowLongPtrW( hwndControl, GWL_STYLE );
        if ((style & (WS_VISIBLE | WS_DISABLED)) == WS_VISIBLE)
        {
            dlgCode = SendMessageW( hwndControl, WM_GETDLGCODE, 0, 0 );
            if ( (dlgCode & (DLGC_BUTTON | DLGC_STATIC)) &&
                 GetWindowTextW( hwndControl, buffer, sizeof(buffer)/sizeof(WCHAR) ))
            {
                /* find the accelerator key */
                LPWSTR p = buffer - 2;

                do
                {
                    p = strchrW( p + 2, '&' );
                }
                while (p != NULL && p[1] == '&');

                /* and check if it's the one we're looking for */
                if (p != NULL && toupperW( p[1] ) == toupperW( wParam ) )
                {
                    if ((dlgCode & DLGC_STATIC) || (style & 0x0f) == BS_GROUPBOX )
                    {
                        /* set focus to the control */
                        SendMessageW( hwndDlg, WM_NEXTDLGCTL, (WPARAM)hwndControl, 1);
                        /* and bump it on to next */
                        SendMessageW( hwndDlg, WM_NEXTDLGCTL, 0, 0);
                    }
                    else if (dlgCode & DLGC_BUTTON)
                    {
                        /* send BM_CLICK message to the control */
                        SendMessageW( hwndControl, BM_CLICK, 0, 0 );
                    }
                    return TRUE;
                }
            }
            hwndNext = GetWindow( hwndControl, GW_CHILD );
        }
        else hwndNext = 0;

        if (!hwndNext) hwndNext = GetWindow( hwndControl, GW_HWNDNEXT );

        while (!hwndNext && hwndControl)
        {
            hwndControl = GetParent( hwndControl );
            if (hwndControl == hwndDlg)
            {
                if(hwnd==hwndDlg)   /* prevent endless loop */
                {
                    hwndNext=hwnd;
                    break;
                }
                hwndNext = GetWindow( hwndDlg, GW_CHILD );
            }
            else
                hwndNext = GetWindow( hwndControl, GW_HWNDNEXT );
        }
        hwndControl = hwndNext;
    }
    while (hwndControl && (hwndControl != hwnd));

    return FALSE;
}