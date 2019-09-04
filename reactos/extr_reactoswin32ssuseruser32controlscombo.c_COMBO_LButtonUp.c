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
struct TYPE_7__ {int wState; int /*<<< orphan*/  hWndLBox; } ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  scalar_t__ INT ;

/* Variables and functions */
 int CBF_BUTTONDOWN ; 
 int CBF_CAPTURE ; 
 int CBF_NOLBSELECT ; 
 int /*<<< orphan*/  CBRepaintButton (TYPE_1__*) ; 
 scalar_t__ CBS_DROPDOWN ; 
 int /*<<< orphan*/  CBUpdateEdit (TYPE_1__*,scalar_t__) ; 
 scalar_t__ CBUpdateLBox (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  SetCapture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void COMBO_LButtonUp( LPHEADCOMBO lphc )
{
   if( lphc->wState & CBF_CAPTURE )
   {
       lphc->wState &= ~CBF_CAPTURE;
       if( CB_GETTYPE(lphc) == CBS_DROPDOWN )
       {
	   INT index = CBUpdateLBox( lphc, TRUE );
	   /* Update edit only if item is in the list */
	   if(index >= 0)
	   {
	       lphc->wState |= CBF_NOLBSELECT;
	       CBUpdateEdit( lphc, index );
	       lphc->wState &= ~CBF_NOLBSELECT;
	   }
       }
       ReleaseCapture();
       SetCapture(lphc->hWndLBox);
   }

   if( lphc->wState & CBF_BUTTONDOWN )
   {
       lphc->wState &= ~CBF_BUTTONDOWN;
       CBRepaintButton( lphc );
   }
}