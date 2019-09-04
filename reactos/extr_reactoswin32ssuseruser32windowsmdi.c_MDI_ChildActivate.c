#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_5__ {scalar_t__ hwndActiveChild; } ;
typedef  TYPE_1__ MDICLIENTINFO ;
typedef  long LPARAM ;
typedef  int /*<<< orphan*/  LONG ;
typedef  scalar_t__ HWND ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetActiveWindow () ; 
 scalar_t__ GetParent (scalar_t__) ; 
 int /*<<< orphan*/  MDI_RefreshMenu (TYPE_1__*) ; 
 int /*<<< orphan*/  MDI_SwitchActiveChild (TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SendMessageW (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long) ; 
 scalar_t__ SetFocus (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*,scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_MDIACTIVATE ; 
 int /*<<< orphan*/  WM_NCACTIVATE ; 
 int /*<<< orphan*/  WM_SETFOCUS ; 
 TYPE_1__* get_client_info (scalar_t__) ; 

__attribute__((used)) static LONG MDI_ChildActivate( HWND client, HWND child )
{
    MDICLIENTINFO *clientInfo;
    HWND prevActiveWnd, frame;
    BOOL isActiveFrameWnd;

    clientInfo = get_client_info( client );

    if (clientInfo->hwndActiveChild == child) return 0;

    TRACE("%p\n", child);

    frame = GetParent(client);
    isActiveFrameWnd = (GetActiveWindow() == frame);
    prevActiveWnd = clientInfo->hwndActiveChild;

    /* deactivate prev. active child */
    if(prevActiveWnd)
    {
        SendMessageW( prevActiveWnd, WM_NCACTIVATE, FALSE, 0L );
        SendMessageW( prevActiveWnd, WM_MDIACTIVATE, (WPARAM)prevActiveWnd, (LPARAM)child);
    }

    MDI_SwitchActiveChild( clientInfo, child, FALSE );
    clientInfo->hwndActiveChild = child;

    MDI_RefreshMenu(clientInfo);

    if( isActiveFrameWnd )
    {
        SendMessageW( child, WM_NCACTIVATE, TRUE, 0L);
        /* Let the client window manage focus for children, but if the focus
         * is already on the client (for instance this is the 1st child) then
         * SetFocus won't work. It appears that Windows sends WM_SETFOCUS
         * manually in this case.
         */
        if (SetFocus(client) == client)
            SendMessageW( client, WM_SETFOCUS, (WPARAM)client, 0 );
    }

    SendMessageW( child, WM_MDIACTIVATE, (WPARAM)prevActiveWnd, (LPARAM)child );
    return TRUE;
}