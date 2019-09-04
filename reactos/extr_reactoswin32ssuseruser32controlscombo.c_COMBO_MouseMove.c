#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_10__ {int wState; int /*<<< orphan*/  hWndLBox; int /*<<< orphan*/  self; int /*<<< orphan*/  buttonRect; } ;
struct TYPE_9__ {short x; short y; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CBF_BUTTONDOWN ; 
 int CBF_CAPTURE ; 
 int /*<<< orphan*/  CBRepaintButton (TYPE_2__*) ; 
 scalar_t__ CBS_DROPDOWN ; 
 int /*<<< orphan*/  CBUpdateLBox (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CB_GETTYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MapWindowPoints (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WM_LBUTTONDOWN ; 

__attribute__((used)) static void COMBO_MouseMove( LPHEADCOMBO lphc, WPARAM wParam, LPARAM lParam )
{
   POINT  pt;
   RECT   lbRect;

   pt.x = (short)LOWORD(lParam);
   pt.y = (short)HIWORD(lParam);

   if( lphc->wState & CBF_BUTTONDOWN )
   {
     BOOL bButton;

     bButton = PtInRect(&lphc->buttonRect, pt);

     if( !bButton )
     {
       lphc->wState &= ~CBF_BUTTONDOWN;
       CBRepaintButton( lphc );
     }
   }

   GetClientRect( lphc->hWndLBox, &lbRect );
   MapWindowPoints( lphc->self, lphc->hWndLBox, &pt, 1 );
   if( PtInRect(&lbRect, pt) )
   {
       lphc->wState &= ~CBF_CAPTURE;
       ReleaseCapture();
       if( CB_GETTYPE(lphc) == CBS_DROPDOWN ) CBUpdateLBox( lphc, TRUE );

       /* hand over pointer tracking */
       SendMessageW(lphc->hWndLBox, WM_LBUTTONDOWN, wParam, lParam);
   }
}