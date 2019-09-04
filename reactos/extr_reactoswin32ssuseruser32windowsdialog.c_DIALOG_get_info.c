#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  idResult; } ;
struct TYPE_8__ {scalar_t__ cbwndExtra; int state; } ;
typedef  TYPE_1__* PWND ;
typedef  int /*<<< orphan*/  HWND ;
typedef  TYPE_2__ DIALOGINFO ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ DLGWINDOWEXTRA ; 
 int /*<<< orphan*/  DWLP_ROS_DIALOGINFO ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDOK ; 
 int /*<<< orphan*/  NtUserxSetDialogPointer (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  SETDLGINFO (int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_1__* ValidateHwnd (int /*<<< orphan*/ ) ; 
 int WNDS_DIALOGWINDOW ; 

DIALOGINFO *DIALOG_get_info( HWND hWnd, BOOL create )
{
    PWND pWindow;
    DIALOGINFO* dlgInfo;

    pWindow = ValidateHwnd( hWnd );
    if (!pWindow)
    {
       return NULL;
    }

    dlgInfo = (DIALOGINFO *)GetWindowLongPtrW( hWnd, DWLP_ROS_DIALOGINFO );

    if (!dlgInfo && create)
    {
        if (pWindow && pWindow->cbwndExtra >= DLGWINDOWEXTRA)
        {
            if (!(dlgInfo = HeapAlloc( GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*dlgInfo) )))
                return NULL;

            dlgInfo->idResult = IDOK;
            SETDLGINFO( hWnd, dlgInfo );
       }
       else
       {
           return NULL;
       }
    }

    if (dlgInfo)
    {
        if (!(pWindow->state & WNDS_DIALOGWINDOW))
        {
           NtUserxSetDialogPointer( hWnd, dlgInfo );
        }
    }
    return dlgInfo;
}