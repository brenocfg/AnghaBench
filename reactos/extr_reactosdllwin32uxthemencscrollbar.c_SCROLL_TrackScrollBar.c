#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ message; scalar_t__ wParam; int /*<<< orphan*/  lParam; } ;
struct TYPE_11__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  int /*<<< orphan*/  PWND_DATA ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__ MSG ;
typedef  int /*<<< orphan*/  INT ;
typedef  scalar_t__ HWND ;

/* Variables and functions */
 scalar_t__ CallMsgFilterW (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClientToScreen (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  DispatchMessageW (TYPE_2__*) ; 
 int /*<<< orphan*/  GET_X_LPARAM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_Y_LPARAM (int /*<<< orphan*/ ) ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  GetMessageW (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (scalar_t__) ; 
 int /*<<< orphan*/  MSGF_SCROLLBAR ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SCROLL_HandleScrollEvent (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,TYPE_1__) ; 
 scalar_t__ SCROLL_TIMER ; 
 int /*<<< orphan*/  ScreenToWindow (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  ThemeGetWndData (scalar_t__) ; 
 int /*<<< orphan*/  TranslateMessage (TYPE_2__*) ; 
 scalar_t__ WM_LBUTTONDOWN ; 
 scalar_t__ WM_LBUTTONUP ; 
 scalar_t__ WM_MOUSEMOVE ; 
 scalar_t__ WM_SYSTIMER ; 

__attribute__((used)) static void 
SCROLL_TrackScrollBar( HWND hwnd, INT scrollbar, POINT pt )
{
    MSG msg;
    PWND_DATA pwndData = ThemeGetWndData(hwnd);
    if(!pwndData)
        return;

    ScreenToWindow(hwnd, &pt);

    SCROLL_HandleScrollEvent(pwndData, hwnd, scrollbar, WM_LBUTTONDOWN, pt );

    do
    {
        if (!GetMessageW( &msg, 0, 0, 0 )) break;
        if (CallMsgFilterW( &msg, MSGF_SCROLLBAR )) continue;
        if (msg.message == WM_LBUTTONUP ||
            msg.message == WM_MOUSEMOVE ||
            (msg.message == WM_SYSTIMER && msg.wParam == SCROLL_TIMER))
        {
            pt.x = GET_X_LPARAM(msg.lParam);
            pt.y = GET_Y_LPARAM(msg.lParam);
            ClientToScreen(hwnd, &pt);
            ScreenToWindow(hwnd, &pt);
            SCROLL_HandleScrollEvent(pwndData, hwnd, scrollbar, msg.message, pt );
        }
        else
        {
            TranslateMessage( &msg );
            DispatchMessageW( &msg );
        }
        if (!IsWindow( hwnd ))
        {
            ReleaseCapture();
            break;
        }
    } while (msg.message != WM_LBUTTONUP && GetCapture() == hwnd);
}