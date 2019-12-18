#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_14__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_18__ {int selected_item; int style; int /*<<< orphan*/  self; TYPE_14__* lphc; scalar_t__ nb_items; } ;
struct TYPE_17__ {scalar_t__ y; scalar_t__ x; } ;
struct TYPE_16__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; } ;
struct TYPE_15__ {int droppedIndex; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int LONG ;
typedef  TYPE_3__ LB_DESCR ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ HWND ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  COMBO_FlipListbox (TYPE_14__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ClientToScreen (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GWL_STYLE ; 
 scalar_t__ GetCapture () ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ GetSystemMetrics (int /*<<< orphan*/ ) ; 
 int GetWindowLongPtrW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ HTHSCROLL ; 
 scalar_t__ HTVSCROLL ; 
 int /*<<< orphan*/  LBN_DBLCLK ; 
 int LBS_NOTIFY ; 
 int /*<<< orphan*/  LISTBOX_HandleLButtonDown (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  LISTBOX_SetCaretIndex (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LISTBOX_SetSelection (TYPE_3__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKELONG (scalar_t__,scalar_t__) ; 
 scalar_t__ PtInRect (TYPE_1__*,TYPE_2__) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SEND_NOTIFICATION (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SM_CXVSCROLL ; 
 int /*<<< orphan*/  SM_CYHSCROLL ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetCapture (scalar_t__) ; 
 scalar_t__ WM_LBUTTONDOWN ; 
 int /*<<< orphan*/  WM_NCLBUTTONDOWN ; 
 int WS_HSCROLL ; 
 int WS_VSCROLL ; 

__attribute__((used)) static LRESULT LISTBOX_HandleLButtonDownCombo( LB_DESCR *descr, UINT msg, DWORD keys, INT x, INT y)
{
    RECT clientRect, screenRect;
    POINT mousePos;

    mousePos.x = x;
    mousePos.y = y;

    GetClientRect(descr->self, &clientRect);

    if(PtInRect(&clientRect, mousePos))
    {
       /* MousePos is in client, resume normal processing */
        if (msg == WM_LBUTTONDOWN)
        {
           descr->lphc->droppedIndex = descr->nb_items ? descr->selected_item : -1;
           return LISTBOX_HandleLButtonDown( descr, keys, x, y);
        }
        else if (descr->style & LBS_NOTIFY)
            SEND_NOTIFICATION( descr, LBN_DBLCLK );
    }
    else
    {
        POINT screenMousePos;
        HWND hWndOldCapture;

        /* Check the Non-Client Area */
        screenMousePos = mousePos;
        hWndOldCapture = GetCapture();
        ReleaseCapture();
        GetWindowRect(descr->self, &screenRect);
        ClientToScreen(descr->self, &screenMousePos);

        if(!PtInRect(&screenRect, screenMousePos))
        {
            LISTBOX_SetCaretIndex( descr, descr->lphc->droppedIndex, FALSE );
            LISTBOX_SetSelection( descr, descr->lphc->droppedIndex, FALSE, FALSE );
            COMBO_FlipListbox( descr->lphc, FALSE, FALSE );
        }
        else
        {
            /* Check to see the NC is a scrollbar */
            INT nHitTestType=0;
            LONG style = GetWindowLongPtrW( descr->self, GWL_STYLE );
            /* Check Vertical scroll bar */
            if (style & WS_VSCROLL)
            {
                clientRect.right += GetSystemMetrics(SM_CXVSCROLL);
                if (PtInRect( &clientRect, mousePos ))
                    nHitTestType = HTVSCROLL;
            }
              /* Check horizontal scroll bar */
            if (style & WS_HSCROLL)
            {
                clientRect.bottom += GetSystemMetrics(SM_CYHSCROLL);
                if (PtInRect( &clientRect, mousePos ))
                    nHitTestType = HTHSCROLL;
            }
            /* Windows sends this message when a scrollbar is clicked
             */

            if(nHitTestType != 0)
            {
                SendMessageW(descr->self, WM_NCLBUTTONDOWN, nHitTestType,
                             MAKELONG(screenMousePos.x, screenMousePos.y));
            }
            /* Resume the Capture after scrolling is complete
             */
            if(hWndOldCapture != 0)
                SetCapture(hWndOldCapture);
        }
    }
    return 0;
}