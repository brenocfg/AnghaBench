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
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GW_OWNER ; 
 int /*<<< orphan*/  GetParent (scalar_t__) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 scalar_t__ GetWindow (scalar_t__,int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__* WIN_ListChildren (int /*<<< orphan*/ ) ; 
 int WS_DISABLED ; 
 int WS_VISIBLE ; 

__attribute__((used)) static HWND MDI_GetWindow(MDICLIENTINFO *clientInfo, HWND hWnd, BOOL bNext,
                            DWORD dwStyleMask )
{
    int i;
    HWND *list;
    HWND last = 0;

    dwStyleMask |= WS_DISABLED | WS_VISIBLE;
    if( !hWnd ) hWnd = clientInfo->hwndActiveChild;

    if (!(list = WIN_ListChildren( GetParent(hWnd) ))) return 0;
    i = 0;
    /* start from next after hWnd */
    while (list[i] && list[i] != hWnd) i++;
    if (list[i]) i++;

    for ( ; list[i]; i++)
    {
        if (GetWindow( list[i], GW_OWNER )) continue;
        if ((GetWindowLongPtrW( list[i], GWL_STYLE ) & dwStyleMask) != WS_VISIBLE) continue;
        last = list[i];
        if (bNext) goto found;
    }
    /* now restart from the beginning */
    for (i = 0; list[i] && list[i] != hWnd; i++)
    {
        if (GetWindow( list[i], GW_OWNER )) continue;
        if ((GetWindowLongPtrW( list[i], GWL_STYLE ) & dwStyleMask) != WS_VISIBLE) continue;
        last = list[i];
        if (bNext) goto found;
    }
 found:
    HeapFree( GetProcessHeap(), 0, list );
    return last;
}