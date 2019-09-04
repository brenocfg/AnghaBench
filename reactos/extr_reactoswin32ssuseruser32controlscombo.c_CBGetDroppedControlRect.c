#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
struct TYPE_9__ {TYPE_1__ droppedRect; int /*<<< orphan*/  self; } ;
struct TYPE_8__ {scalar_t__ top; scalar_t__ bottom; scalar_t__ left; scalar_t__ right; } ;
typedef  TYPE_2__* LPRECT ;
typedef  TYPE_3__* LPHEADCOMBO ;

/* Variables and functions */
 int /*<<< orphan*/  GetWindowRect (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void CBGetDroppedControlRect( LPHEADCOMBO lphc, LPRECT lpRect)
{
    /* In windows, CB_GETDROPPEDCONTROLRECT returns the upper left corner
     of the combo box and the lower right corner of the listbox */

    GetWindowRect(lphc->self, lpRect);

    lpRect->right =  lpRect->left + lphc->droppedRect.right - lphc->droppedRect.left;
    lpRect->bottom = lpRect->top + lphc->droppedRect.bottom - lphc->droppedRect.top;

}