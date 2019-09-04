#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  WNDPROC ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/  OrigWndProc; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  TYPE_1__ IOCS ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CallWindowProcW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCS_Detach (TYPE_1__*) ; 
 int /*<<< orphan*/  IOCS_OnDraw (TYPE_1__*) ; 
 int /*<<< orphan*/  IOCS_OnShow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IOCS_OnSize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  WM_DESTROY 131 
#define  WM_PAINT 130 
#define  WM_SHOWWINDOW 129 
#define  WM_SIZE 128 

__attribute__((used)) static LRESULT IOCS_OnWndProc( IOCS *This, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
    WNDPROC OrigWndProc = This->OrigWndProc;

    switch( uMsg )
    {
        case WM_DESTROY:
            IOCS_Detach( This );
            break;
        case WM_SIZE:
            {
                RECT r;
                SetRect(&r, 0, 0, LOWORD(lParam), HIWORD(lParam));
                IOCS_OnSize( This, &r );
            }
            break;
        case WM_SHOWWINDOW:
            IOCS_OnShow( This, (BOOL) wParam );
            break;
        case WM_PAINT:
            IOCS_OnDraw( This );
            break;
    }

    return CallWindowProcW( OrigWndProc, hWnd, uMsg, wParam, lParam );
}