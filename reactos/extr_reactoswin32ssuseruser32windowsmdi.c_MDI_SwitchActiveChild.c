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
struct TYPE_3__ {scalar_t__ hwndActiveChild; } ;
typedef  TYPE_1__ MDICLIENTINFO ;
typedef  scalar_t__ HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  HWND_TOP ; 
 scalar_t__ IsZoomed (scalar_t__) ; 
 int SWP_NOACTIVATE ; 
 int SWP_NOMOVE ; 
 int SWP_NOSIZE ; 
 int /*<<< orphan*/  SW_MAXIMIZE ; 
 int /*<<< orphan*/  SW_RESTORE ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWindowPos (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ShowWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_SETREDRAW ; 

__attribute__((used)) static void MDI_SwitchActiveChild( MDICLIENTINFO *ci, HWND hwndTo, BOOL activate )
{
    HWND hwndPrev;

    hwndPrev = ci->hwndActiveChild;

    TRACE("from %p, to %p\n", hwndPrev, hwndTo);

    if ( hwndTo != hwndPrev )
    {
        BOOL was_zoomed = IsZoomed(hwndPrev);

        if (was_zoomed)
        {
            /* restore old MDI child */
            SendMessageW( hwndPrev, WM_SETREDRAW, FALSE, 0 );
            ShowWindow( hwndPrev, SW_RESTORE );
            SendMessageW( hwndPrev, WM_SETREDRAW, TRUE, 0 );

            /* activate new MDI child */
            SetWindowPos( hwndTo, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE );
            /* maximize new MDI child */
            ShowWindow( hwndTo, SW_MAXIMIZE );
        }
        /* activate new MDI child */
        SetWindowPos( hwndTo, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | (activate ? 0 : SWP_NOACTIVATE) );
    }
}