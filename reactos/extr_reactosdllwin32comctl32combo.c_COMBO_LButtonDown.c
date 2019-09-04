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
struct TYPE_10__ {int wState; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; } ;
struct TYPE_9__ {short x; short y; } ;
typedef  TYPE_1__ POINT ;
typedef  TYPE_2__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBDropDown (TYPE_2__*) ; 
 int CBF_BUTTONDOWN ; 
 int CBF_CAPTURE ; 
 int CBF_DROPPED ; 
 int /*<<< orphan*/  CBRepaintButton (TYPE_2__*) ; 
 int /*<<< orphan*/  CBRollUp (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ CBS_DROPDOWN ; 
 scalar_t__ CBS_DROPDOWNLIST ; 
 scalar_t__ CB_GETTYPE (TYPE_2__*) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ HIWORD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsWindow (int /*<<< orphan*/ ) ; 
 scalar_t__ LOWORD (int /*<<< orphan*/ ) ; 
 scalar_t__ PtInRect (int /*<<< orphan*/ *,TYPE_1__) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void COMBO_LButtonDown( LPHEADCOMBO lphc, LPARAM lParam )
{
   POINT     pt;
   BOOL      bButton;
   HWND      hWnd = lphc->self;

   pt.x = (short)LOWORD(lParam);
   pt.y = (short)HIWORD(lParam);
   bButton = PtInRect(&lphc->buttonRect, pt);

   if( (CB_GETTYPE(lphc) == CBS_DROPDOWNLIST) ||
       (bButton && (CB_GETTYPE(lphc) == CBS_DROPDOWN)) )
   {
       lphc->wState |= CBF_BUTTONDOWN;
       if( lphc->wState & CBF_DROPPED )
       {
	   /* got a click to cancel selection */

           lphc->wState &= ~CBF_BUTTONDOWN;
           CBRollUp( lphc, TRUE, FALSE );
	   if( !IsWindow( hWnd ) ) return;

           if( lphc->wState & CBF_CAPTURE )
           {
               lphc->wState &= ~CBF_CAPTURE;
               ReleaseCapture();
           }
       }
       else
       {
	   /* drop down the listbox and start tracking */

           lphc->wState |= CBF_CAPTURE;
           SetCapture( hWnd );
           CBDropDown( lphc );
       }
       if( bButton ) CBRepaintButton( lphc );
   }
}