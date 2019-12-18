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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_4__ {int wState; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_1__* LPHEADCOMBO ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int CBF_BUTTONDOWN ; 
 int CBF_NOREDRAW ; 
 scalar_t__ CB_DISABLED (TYPE_1__*) ; 
 int /*<<< orphan*/  DFCS_INACTIVE ; 
 int /*<<< orphan*/  DFCS_PUSHED ; 
 int /*<<< orphan*/  DFCS_SCROLLCOMBOBOX ; 
 int /*<<< orphan*/  DFC_SCROLL ; 
 int /*<<< orphan*/  DrawFrameControl (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void CBPaintButton( LPHEADCOMBO lphc, HDC hdc, RECT rectButton)
{
    UINT buttonState = DFCS_SCROLLCOMBOBOX;

    if( lphc->wState & CBF_NOREDRAW )
      return;


    if (lphc->wState & CBF_BUTTONDOWN)
	buttonState |= DFCS_PUSHED;

    if (CB_DISABLED(lphc))
	buttonState |= DFCS_INACTIVE;

    DrawFrameControl(hdc, &rectButton, DFC_SCROLL, buttonState);
}