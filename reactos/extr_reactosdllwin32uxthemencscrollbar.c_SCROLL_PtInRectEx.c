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
struct TYPE_5__ {int right; int left; int top; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  int /*<<< orphan*/  POINT ;
typedef  TYPE_1__* LPRECT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ PtInRect (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL SCROLL_PtInRectEx( LPRECT lpRect, POINT pt, BOOL vertical )
{
    RECT rect = *lpRect;
    int scrollbarWidth;

    /* Pad hit rect to allow mouse to be dragged outside of scrollbar and
     * still be considered in the scrollbar. */
    if (vertical)
    {
        scrollbarWidth = lpRect->right - lpRect->left;
        rect.left -= scrollbarWidth*8;
        rect.right += scrollbarWidth*8;
        rect.top -= scrollbarWidth*2;
        rect.bottom += scrollbarWidth*2;
    }
    else
    {
        scrollbarWidth = lpRect->bottom - lpRect->top;
        rect.left -= scrollbarWidth*2;
        rect.right += scrollbarWidth*2;
        rect.top -= scrollbarWidth*8;
        rect.bottom += scrollbarWidth*8;
    }
    return PtInRect( &rect, pt );
}