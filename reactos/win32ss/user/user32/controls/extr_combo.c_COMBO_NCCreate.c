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
struct TYPE_5__ {int dwStyle; int /*<<< orphan*/  wState; int /*<<< orphan*/  self; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int LONG_PTR ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HEADCOMBO ;

/* Variables and functions */
 int /*<<< orphan*/  CBF_NOTIFY ; 
 int CBS_HASSTRINGS ; 
 int CBS_OWNERDRAWFIXED ; 
 int CBS_OWNERDRAWVARIABLE ; 
 scalar_t__ COMBO_Init () ; 
 int /*<<< orphan*/  COMBO_update_uistate (TYPE_1__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_EXSTYLE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int WS_BORDER ; 
 int WS_EX_CLIENTEDGE ; 
 int WS_EX_NOPARENTNOTIFY ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 

__attribute__((used)) static LRESULT COMBO_NCCreate(HWND hwnd, LONG style)
{
    LPHEADCOMBO lphc;

    if (COMBO_Init() && (lphc = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(HEADCOMBO))) )
    {
        lphc->self = hwnd;
        SetWindowLongPtrW( hwnd, 0, (LONG_PTR)lphc );

#ifdef __REACTOS__
        COMBO_update_uistate(lphc);
#endif

       /* some braindead apps do try to use scrollbar/border flags */

	lphc->dwStyle = style & ~(WS_BORDER | WS_HSCROLL | WS_VSCROLL);
        SetWindowLongPtrW( hwnd, GWL_STYLE, style & ~(WS_BORDER | WS_HSCROLL | WS_VSCROLL) );

	/*
	 * We also have to remove the client edge style to make sure
	 * we don't end-up with a non client area.
	 */
        SetWindowLongPtrW( hwnd, GWL_EXSTYLE,
                        GetWindowLongPtrW( hwnd, GWL_EXSTYLE ) & ~WS_EX_CLIENTEDGE );

	if( !(style & (CBS_OWNERDRAWFIXED | CBS_OWNERDRAWVARIABLE)) )
              lphc->dwStyle |= CBS_HASSTRINGS;
	if( !(GetWindowLongPtrW( hwnd, GWL_EXSTYLE ) & WS_EX_NOPARENTNOTIFY) )
	      lphc->wState |= CBF_NOTIFY;

        TRACE("[%p], style = %08x\n", lphc, lphc->dwStyle );
        return TRUE;
    }
    return FALSE;
}