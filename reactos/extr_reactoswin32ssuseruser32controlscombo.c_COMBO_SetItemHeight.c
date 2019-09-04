#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_8__ {int editHeight; int /*<<< orphan*/  hWndLBox; int /*<<< orphan*/  droppedRect; int /*<<< orphan*/  textRect; int /*<<< orphan*/  buttonRect; int /*<<< orphan*/  self; } ;
typedef  int LRESULT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;

/* Variables and functions */
 int /*<<< orphan*/  CBCalcPlacement (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CBForceDummyResize (TYPE_1__*) ; 
 int /*<<< orphan*/  CBResetPos (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ CBS_SIMPLE ; 
 int CB_ERR ; 
 scalar_t__ CB_GETTYPE (TYPE_1__*) ; 
 scalar_t__ CB_OWNERDRAWN (TYPE_1__*) ; 
 int /*<<< orphan*/  LB_SETITEMHEIGHT ; 
 int SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT COMBO_SetItemHeight( LPHEADCOMBO lphc, INT index, INT height )
{
   LRESULT	lRet = CB_ERR;

   if( index == -1 ) /* set text field height */
   {
       if( height < 32768 )
       {
           lphc->editHeight = height + 2;  /* Is the 2 for 2*EDIT_CONTROL_PADDING? */

	 /*
	  * Redo the layout of the control.
	  */
	 if ( CB_GETTYPE(lphc) == CBS_SIMPLE)
	 {
	   CBCalcPlacement(lphc->self,
			   lphc,
			   &lphc->textRect,
			   &lphc->buttonRect,
			   &lphc->droppedRect);

	   CBResetPos( lphc, &lphc->textRect, &lphc->droppedRect, TRUE );
	 }
	 else
	 {
	   CBForceDummyResize(lphc);
	 }

	   lRet = height;
       }
   }
   else if ( CB_OWNERDRAWN(lphc) )	/* set listbox item height */
       lRet = SendMessageW(lphc->hWndLBox, LB_SETITEMHEIGHT, (WPARAM)index, (LPARAM)height);
   return lRet;
}