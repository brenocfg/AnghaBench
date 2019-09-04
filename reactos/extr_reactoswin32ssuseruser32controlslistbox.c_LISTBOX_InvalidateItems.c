#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int style; int /*<<< orphan*/  self; int /*<<< orphan*/  width; int /*<<< orphan*/  height; } ;
struct TYPE_7__ {scalar_t__ top; int /*<<< orphan*/  right; int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ LB_DESCR ;
typedef  int /*<<< orphan*/  INT ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidateRect (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int LBS_DISPLAYCHANGED ; 
 int LBS_MULTICOLUMN ; 
 int LBS_NOREDRAW ; 
 int LISTBOX_GetItemRect (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void LISTBOX_InvalidateItems( LB_DESCR *descr, INT index )
{
    RECT rect;

    if (LISTBOX_GetItemRect( descr, index, &rect ) == 1)
    {
        if (descr->style & LBS_NOREDRAW)
        {
            descr->style |= LBS_DISPLAYCHANGED;
            return;
        }
        rect.bottom = descr->height;
        InvalidateRect( descr->self, &rect, TRUE );
        if (descr->style & LBS_MULTICOLUMN)
        {
            /* Repaint the other columns */
            rect.left  = rect.right;
            rect.right = descr->width;
            rect.top   = 0;
            InvalidateRect( descr->self, &rect, TRUE );
        }
    }
}