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
struct TYPE_5__ {int wState; } ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CBDropDown (TYPE_1__*) ; 
 int CBF_DROPPED ; 
 int /*<<< orphan*/  CBRollUp (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

BOOL COMBO_FlipListbox( LPHEADCOMBO lphc, BOOL ok, BOOL bRedrawButton )
{
   if( lphc->wState & CBF_DROPPED )
   {
       CBRollUp( lphc, ok, bRedrawButton );
       return FALSE;
   }

   CBDropDown( lphc );
   return TRUE;
}