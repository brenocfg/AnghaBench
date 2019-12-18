#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_4__ {int wState; int /*<<< orphan*/  textRect; int /*<<< orphan*/  self; int /*<<< orphan*/  hWndLBox; } ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  scalar_t__ INT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int CBF_EDIT ; 
 int /*<<< orphan*/  CBUpdateEdit (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LB_SELECTSTRING ; 
 scalar_t__ SendMessageA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SendMessageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static LRESULT COMBO_SelectString( LPHEADCOMBO lphc, INT start, LPARAM pText, BOOL unicode )
{
   INT index = unicode ? SendMessageW(lphc->hWndLBox, LB_SELECTSTRING, (WPARAM)start, pText) :
                         SendMessageA(lphc->hWndLBox, LB_SELECTSTRING, (WPARAM)start, pText);
   if( index >= 0 )
   {
     if( lphc->wState & CBF_EDIT )
       CBUpdateEdit( lphc, index );
     else
     {
       InvalidateRect(lphc->self, &lphc->textRect, TRUE);
     }
   }
   return (LRESULT)index;
}