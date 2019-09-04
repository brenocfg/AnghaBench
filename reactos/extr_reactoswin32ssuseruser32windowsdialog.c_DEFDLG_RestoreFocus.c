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
struct TYPE_3__ {int flags; int /*<<< orphan*/ * hwndFocus; } ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  TYPE_1__ DIALOGINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DEFDLG_SetFocus (int /*<<< orphan*/ *) ; 
 int DF_END ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* GETDLGINFO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetNextDlgGroupItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * GetNextDlgTabItem (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsIconic (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFocus (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void DEFDLG_RestoreFocus( HWND hwnd, BOOL justActivate )
{
    DIALOGINFO *infoPtr;

    if (IsIconic( hwnd )) return;
    if (!(infoPtr = GETDLGINFO(hwnd))) return;
    /* Don't set the focus back to controls if EndDialog is already called.*/
    if (infoPtr->flags & DF_END) return;
    if (!IsWindow(infoPtr->hwndFocus) || infoPtr->hwndFocus == hwnd) {
        if (justActivate) return;
        /* If no saved focus control exists, set focus to the first visible,
           non-disabled, WS_TABSTOP control in the dialog */
        infoPtr->hwndFocus = GetNextDlgTabItem( hwnd, 0, FALSE );
        /* If there are no WS_TABSTOP controls, set focus to the first visible,
           non-disabled control in the dialog */
        if (!infoPtr->hwndFocus) infoPtr->hwndFocus = GetNextDlgGroupItem( hwnd, 0, FALSE );
        if (!IsWindow( infoPtr->hwndFocus )) return;
    }
    if (justActivate)
        SetFocus( infoPtr->hwndFocus );
    else
        DEFDLG_SetFocus( infoPtr->hwndFocus );

    infoPtr->hwndFocus = NULL;
}