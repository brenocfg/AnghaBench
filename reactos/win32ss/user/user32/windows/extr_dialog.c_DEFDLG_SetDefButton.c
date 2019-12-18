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
struct TYPE_3__ {int /*<<< orphan*/  idResult; } ;
typedef  scalar_t__ HWND ;
typedef  int DWORD ;
typedef  TYPE_1__ DIALOGINFO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETSTYLE ; 
 int /*<<< orphan*/  BS_DEFPUSHBUTTON ; 
 int /*<<< orphan*/  BS_PUSHBUTTON ; 
 scalar_t__ DEFDLG_FindDefButton (scalar_t__) ; 
 int DLGC_DEFPUSHBUTTON ; 
 int DLGC_UNDEFPUSHBUTTON ; 
 scalar_t__ GetDlgItem (scalar_t__,int /*<<< orphan*/ ) ; 
 int SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_GETDLGCODE ; 

__attribute__((used)) static BOOL DEFDLG_SetDefButton( HWND hwndDlg, DIALOGINFO *dlgInfo, HWND hwndNew )
{
    DWORD dlgcode=0; /* initialize just to avoid a warning */
    HWND hwndOld = GetDlgItem( hwndDlg, dlgInfo->idResult );

    if (hwndNew &&
        !((dlgcode=SendMessageW(hwndNew, WM_GETDLGCODE, 0, 0 ))
            & (DLGC_UNDEFPUSHBUTTON | DLGC_DEFPUSHBUTTON)))
    {
        /**
         * Need to draw only default push button rectangle.
         * Since the next control is not a push button, need to draw the push
         * button rectangle for the default control.
         */
        hwndNew = hwndOld;
        dlgcode = SendMessageW(hwndNew, WM_GETDLGCODE, 0, 0 );
    }

    /* Make sure the old default control is a valid push button ID */
    if (!hwndOld || !(SendMessageW( hwndOld, WM_GETDLGCODE, 0, 0) & DLGC_DEFPUSHBUTTON))
        hwndOld = DEFDLG_FindDefButton( hwndDlg );
    if (hwndOld && hwndOld != hwndNew)
        SendMessageW( hwndOld, BM_SETSTYLE, BS_PUSHBUTTON, TRUE );

    if (hwndNew)
    {
        if(dlgcode & DLGC_UNDEFPUSHBUTTON)
            SendMessageW( hwndNew, BM_SETSTYLE, BS_DEFPUSHBUTTON, TRUE );
    }
    return TRUE;
}